#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *infile,*outfile;
void Compress(char *infilename,char *outfilename);
void Common(char *filename);

//压缩失败
void Common(char *filename)
{
	char tempspace[200];
	strcpy(tempspace,"Unable to open");
	strcat(tempspace,filename);
	puts(tempspace);
	exit(0);
}

//压缩函数
void Compress(char *infilename,char *outfilename)
{
	register int seq_len;
	char cur_char,cur_seq;
	if((infile=fopen(infilename,"rb"))==NULL)
		Common(infilename);
	if((outfile=fopen(outfilename,"wb"))==NULL)
		Common(outfilename);
	cur_char=fgetc(infile);
	cur_seq=cur_char;
	seq_len=1;
	
	while(!feof(infile))
	{
		cur_char=fgetc(infile);
		if(cur_char==cur_seq)
		{
			seq_len++;
		}
		else
		{
			fputc(seq_len,outfile);
			fputc(cur_seq,outfile);
			cur_seq=cur_char;
			seq_len=1;
		}		
	}
}

//主体函数
int main(int argc, char* argv[])
{
	printf("relys compress file\n");
	if(argc!=3)
	{
		printf("\n usage:relys sourcefilename targetfilename\n");
		exit(0);
	}
	
	printf("\n Compression...");
	Compress(argv[1],argv[2]);
	fclose(infile);
	fclose(outfile);
	printf("\n");
	return 0;
}
