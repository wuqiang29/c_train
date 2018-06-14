/*
*RLE能压缩任何二进制数据，原始图像文件的数据有一个特点，那就是有大量连续重复的颜色数据，RLE正好是用来压缩有大量连续重复数据的压缩编码，但对于
*其他二进制文件而言，由于文件中相同的数据出现概率较少，使用RLE压缩这些数据重复不强的文件效果不太理想，又是压缩后的数据反而变大了。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *infile,*outfile;
void Decompress(char *infilename, char *outfilename);
//void Compress(char *filename);
void Common(char *filename);

int main(int argc, char* argv[])
{
	printf("\n rlejy decompress file...\n");
	if(argc!=3)
	{
		printf("\n usage:rlejy sourcefilename targetfilename\n");
		exit(0);
	}
	printf("\n decompression...");
	Decompress(argv[1],argv[2]);
	fclose(infile);
	fclose(outfile);
	return 0;
}

void Common(char *filename)
{
	char tempspace[200];
	strcpy(tempspace,"\nUnable to open");
	strcat(tempspace,filename);
	puts(tempspace);
	exit(1);
}

void Decompress(char *infilename,char *outfilename)
{
	register int seq_len, i;
	char cur_char;
	if((infile=fopen(infilename,"rb"))==NULL)
		Common(infilename);
	if((outfile=fopen(outfilename,"wb"))==NULL)
		Common(outfilename);

	while(!feof(infile))
	{
		seq_len=fgetc(infile);
		cur_char=fgetc(infile);

		for(i=0;i<seq_len;i++)
		{
			fputc(cur_char,outfile);
		}	
	}

}
