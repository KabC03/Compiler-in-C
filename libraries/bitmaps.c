//25, Jul, 2024
#include "bitmaps.h"
#define BITMAP_FILE_SIGNATURE 0x4D42
#define BITS_PER_BYTE 8
#define PAD_CONSTANT 4
/*
TODO: 
- Draw a line accross an image
- Create a blank image with a background colour
- Export an array and header data to a bitmap
- Resize an image
- Currently only supports 24 bit depth - make it support at least 32 and 16 bit depth too
*/




/**
 * bitmap_enstantiate 
 * ===============================================
 * Brief: Enstantiate a bitmap image - must be manually closed before program ends
 * 
 * Param: *bitmapPath - Path to an empty bitmap struct
 *        *bitmapImageOutput - data of interest
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_enstantiate(char *bitmapPath, BitmapImage *bitmapImageOutput) {

    if(bitmapPath == NULL || bitmapImageOutput == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        FILE *bitmapFptr = fopen(bitmapPath, "rb");
        if(bitmapFptr == NULL) {
            return _FILE_NOT_OPENED_; 
        }


        //Leave this opened until manually closed
        bitmapImageOutput->bitmapImagePtr = bitmapFptr;

        //Read header
        if(fread(&(bitmapImageOutput->bitmapHeader), sizeof(BitmapHeader), 1, bitmapFptr) != 1) {
            return _INTERNAL_ERROR_;
        }
        //Read the metadata
        if(fread(&(bitmapImageOutput->bitmapMetadata), sizeof(BitmapMetadata), 1, bitmapFptr) != 1) {
            return _INTERNAL_ERROR_;
        }


        //Check file is a bitmap
        if(bitmapImageOutput->bitmapHeader.fileType != BITMAP_FILE_SIGNATURE) {
            return _INTERNAL_ERROR_;
        }

        //Read data into a vector - NOTE: CURRENTLY < 8 BIT PIXEL DEPTH NOT SUPPORTED

        size_t bytesPerPixel = (bitmapImageOutput->bitmapMetadata.bitsPerPixel)/BITS_PER_BYTE;
        size_t numberOfPixelsInRow = bitmapImageOutput->bitmapMetadata.imageWidth;
        size_t numberOfPixelsInCol = bitmapImageOutput->bitmapMetadata.imageHeight;

        size_t paddingPerRow = (PAD_CONSTANT - (bitmapImageOutput->bitmapMetadata.imageWidth * bytesPerPixel % PAD_CONSTANT)) % PAD_CONSTANT;

        if(vector_initialise(&(bitmapImageOutput->bitmapData), bytesPerPixel) == false) {
            return _INTERNAL_ERROR_;
        }
        void *tempBuffer = malloc(numberOfPixelsInRow * bytesPerPixel);
        if(tempBuffer == NULL) {
            return _ALLOC_FAILURE_;
        }

        //Seek passed the metadata
        if(fseek(bitmapFptr, bitmapImageOutput->bitmapHeader.dataOffset, SEEK_SET) != 0) {
            return _INTERNAL_ERROR_;
        }


        for(size_t i = 0; i < numberOfPixelsInCol; i++) {

            //Read all pixels
            if(fread(tempBuffer, bytesPerPixel, numberOfPixelsInRow, bitmapFptr) != numberOfPixelsInRow) {
                return _INTERNAL_ERROR_;
            }


            //Write numberOfPixels from tempBuffer
            if(vector_quick_append(&(bitmapImageOutput->bitmapData), tempBuffer, numberOfPixelsInRow) == false) {
                return _INTERNAL_ERROR_;
            }

            if(paddingPerRow != 0) {

                //Skip passed padding
                if(fseek(bitmapFptr, paddingPerRow, SEEK_CUR) != 0) {
                    return _INTERNAL_ERROR_;
                }
            }
        }






        free(tempBuffer);
    }

    return _SUCCESS_;
}








/**
 * bitmap_greyscale 
 * ===============================================
 * Brief: Greyscales a bitmap image 
 * 
 * Param: *bitmapImage - Enstantiated bitmap of interest 
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_greyscale(BitmapImage *bitmapImage) {

    if(bitmapImage == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        //Have to place this here otherwies compiler complains
        //Gray = 0.299 * R + 0.587 * G + 0.144 * B 
        uint8_t red = 0;
        uint8_t blue= 0;
        uint8_t green = 0;

        uint8_t grey = 0;

        uint32_t *pixel = 0;


        size_t numberOfPixels = vector_get_length(&(bitmapImage->bitmapData)) + 1;
        //Will add more depths later
        




        switch (bitmapImage->bitmapMetadata.bitsPerPixel) {
        case 24:


            for(size_t i = 0; i < numberOfPixels; i++) {

                pixel = (uint32_t*)vector_get_index(&(bitmapImage->bitmapData), i);
                if(pixel == NULL) {
                    //Unexpected NULL ptr - will make better later
                    return _INTERNAL_ERROR_;
                }

                //WARNING: assuming BGR format
                blue = (*pixel) & (0xFF); //255
                green = ((*pixel) & (0xFF00)) >> 8; //65280 then bitshift down 8 bits
                red = ((*pixel) & (0xFF0000)) >> 16; //Same thing again


                //Set greyscale
                grey = (0.299 * red) + (0.587 * green) + (0.144 * blue);
                uint32_t newPixel = grey;
                newPixel <<= 8;
                newPixel += grey;
                newPixel <<= 8;
                newPixel += grey;

                //printf("Blue: %d, Green: %d, Red: %d, Grey: %d\n", blue, green, red, newPixel);

                //Set new greyscale pixel
                if(vector_set_index(&(bitmapImage->bitmapData), i, &newPixel) == false) {
                    return _INTERNAL_ERROR_;
                }

            }
            
            
            break;
        
        default:
            return _INTERNAL_ERROR_;
            break;
        }





    }

    return _SUCCESS_;
}






/**
 * bitmap_reconstruct_image 
 * ===============================================
 * Brief: Reconstruct an image from a bitmap 
 * 
 * Param: *bitmapImage - Bitmap of interest 
 *        *imagePath - Name for the image to be produced
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_reconstruct_image(BitmapImage *bitmapImage, char *imagePath) {

    if(bitmapImage == NULL || imagePath == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        //Write the metadata
        //Reconstruct the data (pad it) 

        FILE *producedImagePtr = fopen(imagePath, "wb");
        if(producedImagePtr == NULL) {
            return _FILE_NOT_OPENED_;
        }



        //Write the metadata
        if(fwrite(&(bitmapImage->bitmapHeader), sizeof(BitmapHeader), 1, producedImagePtr) != 1) {
            return _INTERNAL_ERROR_;
        }

        if(fwrite(&(bitmapImage->bitmapMetadata), sizeof(BitmapMetadata), 1, producedImagePtr) != 1) {
            return _INTERNAL_ERROR_;
        }




        //Reconstruct the image
        size_t bytesPerPixel = (bitmapImage->bitmapMetadata.bitsPerPixel)/BITS_PER_BYTE;
        size_t numberOfPixelsInRow = bitmapImage->bitmapMetadata.imageWidth;
        size_t numberOfPixelsInCol = bitmapImage->bitmapMetadata.imageHeight;
        size_t paddingPerRow = (PAD_CONSTANT - (bitmapImage->bitmapMetadata.imageWidth * bytesPerPixel % PAD_CONSTANT)) % PAD_CONSTANT;


        //Write the row, then padding 

        void *padding = NULL;
        if(paddingPerRow != 0) {
            padding = calloc(paddingPerRow, 1);

            if(padding == NULL) {
                return _ALLOC_FAILURE_;
            }
        }


        for(size_t i = 0; i < numberOfPixelsInCol; i++) {

            //Writing row by row - therefore have to multiply by the size of the pixels
            const void *dataToBeWritten = vector_get_index(&(bitmapImage->bitmapData), i * numberOfPixelsInRow);
            //Write the pixels
            if(fwrite(dataToBeWritten, numberOfPixelsInRow * bytesPerPixel, 1, producedImagePtr) != 1) {
                return _INTERNAL_ERROR_;
            }


            if(paddingPerRow != 0) {
                //Write the padding
                if(fwrite(padding, paddingPerRow, 1, producedImagePtr) != 1) {
                    return _INTERNAL_ERROR_;
                }
            }

        }
    }

    return _SUCCESS_;
}







/**
 * bitmap_destroy 
 * ===============================================
 * Brief: Destroy all associated memory with a bitmap 
 * 
 * Param: *bitmapImage - Bitmap of interest 
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_destroy(BitmapImage *bitmapImage) {

    if(bitmapImage == NULL) {
        return _INVALID_ARG_PASS_;
    } else {

        vector_destroy(&(bitmapImage->bitmapData));
    }

    return _SUCCESS_;
}



/**
 * bitmap_return_metadata
 * ===============================================
 * Brief: Return metadata for an image 
 * 
 * Param: *bitmapImage - Bitmap of interest 
 *        *outputMetadata 
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_return_metadata(BitmapImage *bitmapImage, BitmapMetadata *outputMetadata) {

    if(bitmapImage == NULL || outputMetadata == NULL) {
        return _INVALID_ARG_PASS_;

    } else {

        *outputMetadata = bitmapImage->bitmapMetadata;
    }

    return _SUCCESS_;
}





