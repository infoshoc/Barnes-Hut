#include <Windows.h>
#include <string>
using namespace std;

void SaveBitmapToFileColor( RGBTRIPLE *pBitmapBits, LONG lWidth, LONG lHeight, WORD wBitsPerPixel, const char *file_name ){

    BITMAPINFOHEADER bmpInfoHeader;
    // Set the size
    bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    // Bit count
    bmpInfoHeader.biBitCount = wBitsPerPixel;
    // Use all colors
    bmpInfoHeader.biClrImportant = 0;
    // Use as many colors according to bits per pixel
    bmpInfoHeader.biClrUsed = 0;
    // Store as un Compressed
    bmpInfoHeader.biCompression = BI_RGB;
    // Set the height in pixels
    bmpInfoHeader.biHeight = lHeight;
    // Width of the Image in pixels
    bmpInfoHeader.biWidth = lWidth;
    // Default number of planes
    bmpInfoHeader.biPlanes = 1;
    // Calculate the image size in bytes
    bmpInfoHeader.biSizeImage = lWidth* lHeight * (wBitsPerPixel/8);

    BITMAPFILEHEADER bfh;
    // This value should be values of BM letters i.e 0x4D42
    // 0x4D = M 0?42 = B storing in reverse order to match with endian

    bfh.bfType = 'B'+('M' << 8);
    // <<8 used to shift ‘M’ to end

    // Offset to the RGBQUAD
    bfh.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
    // Total size of image including size of headers
    bfh.bfSize = bfh.bfOffBits + bmpInfoHeader.biSizeImage;
    // Create the file in disk to write
	FILE *fh = fopen ( file_name, "wb" );

    if( fh == NULL ) // return if error opening file
    {
        return;
    }

    //DWORD dwWritten = 0;
    // Write the File header
	fwrite ( &bfh, sizeof ( bfh ), 1, fh );
    // Write the bitmap info header
	fwrite ( &bmpInfoHeader, sizeof(bmpInfoHeader), 1, fh );
    // Write the palette
    //WriteFile( hFile, &palette[0], sizeof(RGBQUAD) * 256, &dwWritten, NULL );
    // Write the RGB Data
    if(lWidth%4 == 0)
    {
		fwrite ( pBitmapBits, bmpInfoHeader.biSizeImage, 1, fh );
    }
    else
    {
        char* empty = new char[ 4 - lWidth % 4];
        for(int i = 0; i < lHeight; ++i)
        {
			fwrite ( &pBitmapBits[i * lWidth], lWidth, 1, fh );
			fwrite ( empty, 4 - lWidth % 4, 1, fh );
        }
    }
    // Close the file handle
	fclose ( fh );
}
