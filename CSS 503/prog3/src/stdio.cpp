// STDIO.CPP
// Author: Professor Dimpsey
// Edited by: Erika Parayno (SID #: 1425156)
// Description: Completed implementation of standard i/o operations. Using buffer variables, we are
// 					building on top of system calls to build a new set of I/O methods that takes
//						advantage of cache buffer system.
// Assumptions:	- contains text files to read (hamlet.txt & othello.txt)
// 					- contains appropriate drivers to run program, which includes stdio.h
//						- stdio.h includes stdio.cpp at end of class

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
using namespace std;
char decimal[100];

// Description: recursively gets string from int
// Pre-condition: accepts an int argument
// Post-condition: returns string
int recursive_itoa(int arg)
{
	int div = arg / 10;
	int mod = arg % 10;
	int index = 0;
	if (div > 0)
	{
		index = recursive_itoa(div);
	}
	decimal[index] = mod + '0';
	return ++index;
}

// Description: gets a string from int
// Pre-condition: accepts an int argument
// Post-condition: returns string
char *itoa(const int arg)
{
	bzero(decimal, 100);
	int order = recursive_itoa(arg);
	char *new_decimal = new char[order + 1];
	bcopy(decimal, new_decimal, order + 1);
	return new_decimal;
}

// Description: formatted print method
// Pre-condition: accepts string parameter followed by other parameters
// Post-condition: prints message to user
int printf(const void *format, ...)
{
	va_list list;
	va_start(list, format);

	char *msg = (char *)format;
	char buf[1024];
	int nWritten = 0;

	int i = 0, j = 0, k = 0;
	while (msg[i] != '\0')
	{
		if (msg[i] == '%' && msg[i + 1] == 'd')
		{
			buf[j] = '\0';
			nWritten += write(1, buf, j);
			j = 0;
			i += 2;

			int int_val = va_arg(list, int);
			char *dec = itoa(abs(int_val));
			if (int_val < 0)
			{
				nWritten += write(1, "-", 1);
			}
			nWritten += write(1, dec, strlen(dec));
			delete dec;
		}
		else
		{
			buf[j++] = msg[i++];
		}
	}
	if (j > 0)
	{
		nWritten += write(1, buf, j);
	}
	va_end( list );
	return nWritten;
}

// Description: sets the size of an input / output stream buffer
// Pre-condition: accepts information about stream, buffer, mode, and size
// Post-condition: adjust stream size to paramter size based on mode
int setvbuf(FILE *stream, char *buf, int mode, size_t size)
{
	if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF)
	{
		return -1;
	}
	stream->mode = mode;
	stream->pos = 0;
	if (stream->buffer != (char *)0 && stream->bufown == true)
	{
		delete stream->buffer;
	}

	switch ( mode )
	{
		case _IONBF:
			stream->buffer = (char *)0;
			stream->size = 0;
			stream->bufown = false;
			break;
		case _IOLBF:
		case _IOFBF:
			if (buf != (char *)0)
			{
				stream->buffer = buf;
				stream->size   = size;
				stream->bufown = false;
			}
			else
			{
				stream->buffer = new char[BUFSIZ];
				stream->size = BUFSIZ;
				stream->bufown = true;
			}
			break;
	}
	return 0;
}

// Description: sets the size of an input / output stream buffer
// Pre-condition: accepts stream and buffer parameters
// Post-condition: calls setvbuf with the corresponding parameters and _IONBF & BUFSIZ as default mode and stream size respectively
void setbuf(FILE *stream, char *buf)
{
	setvbuf(stream, buf, ( buf != (char *)0 ) ? _IOFBF : _IONBF , BUFSIZ);
}

// Description: opens file and sets flag based on mode
// Pre-condition: accepts path and mode that will determine whether it is read, write, etc.
// Post-condition: returns stream if succesful
FILE *fopen(const char *path, const char *mode)
{
	FILE *stream = new FILE();
	setvbuf(stream, (char *)0, _IOFBF, BUFSIZ);

	// fopen( ) mode
	// r or rb = O_RDONLY
	// w or wb = O_WRONLY | O_CREAT | O_TRUNC
	// a or ab = O_WRONLY | O_CREAT | O_APPEND
	// r+ or rb+ or r+b = O_RDWR
	// w+ or wb+ or w+b = O_RDWR | O_CREAT | O_TRUNC
	// a+ or ab+ or a+b = O_RDWR | O_CREAT | O_APPEND

	switch(mode[0])
	{
		case 'r':
			if (mode[1] == '\0')            // r
			{
				stream->flag = O_RDONLY;
			}
			else if ( mode[1] == 'b' )
			{
				if (mode[2] == '\0')          // rb
				{
					stream->flag = O_RDONLY;
				}
				else if (mode[2] == '+')      // rb+
				{
					stream->flag = O_RDWR;
				}
			}
			else if (mode[1] == '+')        // r+  r+b
			{
				stream->flag = O_RDWR;
			}
			break;
		case 'w':
			if (mode[1] == '\0')            // w
			{
				stream->flag = O_WRONLY | O_CREAT | O_TRUNC;
			}
			else if (mode[1] == 'b')
			{
				if (mode[2] == '\0')          // wb
				{
					stream->flag = O_WRONLY | O_CREAT | O_TRUNC;
				}
				else if (mode[2] == '+')      // wb+
				{
					stream->flag = O_RDWR | O_CREAT | O_TRUNC;
				}
			}
			else if (mode[1] == '+')        // w+  w+b
			{
				stream->flag = O_RDWR | O_CREAT | O_TRUNC;
			}
			break;
		case 'a':
			if (mode[1] == '\0')            // a
			{
				stream->flag = O_WRONLY | O_CREAT | O_APPEND;
			}
			else if (mode[1] == 'b')
			{
				if (mode[2] == '\0')          // ab
				{
					stream->flag = O_WRONLY | O_CREAT | O_APPEND;
				}
				else if (mode[2] == '+')      // ab+
				{
					stream->flag = O_RDWR | O_CREAT | O_APPEND;
				}
			}
			else if (mode[1] == '+')        // a+  a+b
			{
				stream->flag = O_RDWR | O_CREAT | O_APPEND;
			}
			break;
	}

	mode_t open_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	if ((stream->fd = open(path, stream->flag, open_mode)) == -1)
	{
		delete stream;
		printf("fopen failed\n");
		stream = NULL;
	}
	return stream;
}

// Description: clears an input / output stream buffer
// Pre-condition: accepts stream, usually called when you need to clear buffer during the fread functions
// Post-condition: clears buffer, sets position and acutaul size to 0, and returns 0 if successful
int fpurge(FILE *stream)
{
	if (stream == nullptr) {
		return EOF;
	}
	else {
		// clear buffer
		memset(stream->buffer, '\0', stream->size);
		// restart position at 0;
		stream->pos = 0;
		// we cleared the buffer, so readjust size to 0 
		stream->actual_size = 0;
		// successful, so return 0
		return 0;
	}
}

// Description: synchronizes an output stream with the actual file
// Pre-condition: accepts stream, usually called when you need position has reached the end of buffer, and need to write buffer contents to device
// Post-condition: writes to device, clears buffer, resets position and actual size, and returns 0 if successful
int fflush(FILE *stream)	// complete it
{
	if (stream == nullptr) {
		return EOF;
	}
	else {
		// write on to device
		int bytesWritten = write(stream->fd, stream->buffer, stream->pos);
		// change last op to write
		stream->lastop = 'w';
		// if nothing was written, return EOF
		if (bytesWritten == -1) {
			return EOF;
		}
		// clear buffer
		memset(stream->buffer, '\0', stream->size);
		// reset actual size to 0 since we cleared the buffer
		stream->actual_size = 0;
		// restart position pointer to 0
		stream->pos = 0;
		// successful, so return 0
		return 0;
	}
}

// Description: reads a character from a file stream
// Pre-condition: accepts stream to get character from as parameter
// Post-condition: returns character at that position in the file stream
int fgetc(FILE *stream)
{
	// If buffer was used in write previously, clear buffer
	if (stream->lastop == 'w') {
		fpurge(stream);
	}
	// if we've read through the entire buffer size
	if (stream->actual_size == 0) {
		// clear buffer
		fpurge(stream);
		// refill
		int refillSize = read(stream->fd, stream->buffer, stream->size);
		// set last operation condition to read
		stream->lastop = 'r';
		// adjust actual size to new refill size
		stream->actual_size = refillSize;
		// if new actual_size is equal to zero, it is empty, and we reached eof
		if(stream->actual_size <= 0 ) {
			stream->eof = true;
			return EOF;
		}
		// restart position pointer to the beginning buffer
		stream->pos = 0;
	}
	// if there is more to read in the buffer
	else {
		// increment position
		stream->pos++;
	}
	// read one char from buffer
	int ch = stream->buffer[stream->pos];
	// we've read an extra ch, so decrement according to its size
	stream->actual_size -= sizeof((char) ch);
	// return char value
	return ch;
}

// Description: reads from a file
// Pre-condition: accepts pointer to object in userspace to store data into with corresponding size & number of mebmers, along with the stream to read from
// Post-condition: Returns itemsRead successfully read
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	// initialize counter
	int byteCounter = 0;
	// cast ptr to unsigned char
	auto* buffPtr = static_cast<unsigned char*>(ptr);
	// while number of bytes read is less than entire size to read
	while (byteCounter < (nmemb * size)) {
		// get one byte at a time
		int cint = fgetc(stream);
		// if we've reached end of file, break
		if (cint == EOF) {
			stream->eof = true;
			break;
		}
		// copy character into the userspace buffer
		*buffPtr = cint;
		// increment userspace buffer pointer
		buffPtr++;
		// increment bytes read by size of character
		byteCounter += sizeof((char) cint);
	}
	// calculate number of items successfully read
	int itemsRead = byteCounter / size;
	// returns the number of full items successfully read
	return itemsRead;
}

// Description: writes a character to a file stream
// Pre-condition: accepts a character and the stream to write that character into
// Post-condition: Returns positive value if the character was successfully added to stream's buffer. Else it returns EOF. 
int fputc(int c, FILE *stream)
{
	// if buffer previously used for read, it wouldn't
	if (stream->lastop == 'r') {
		fpurge(stream);
	}
	// if the position pointer reached the end of the buffer
	if (stream->pos == stream->size) {
		// write the buffer into output file, clear buffer, and restart at 0 using flush
		int writtenToFile = fflush(stream);
		// if we tried to write EOF, then return EOF
		if (writtenToFile == EOF) {
			stream->eof = true;
			return EOF;
		}
	}
	// place character into buffer at current position
	stream->buffer[stream->pos] = c;
	// increment position counter
	stream->pos++;
	// return 0 as it is successful
	return c;
}

// Description: writes to a file
// Pre-condition: contains pointer to array with corresponding size & number of members, and stream to write to
// Post-condition: returns number of items successfully added to target stream's buffer 
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	// initialize counter
	int byteCounter = 0;
	// cast void pointer to char pointer
	const auto* buffPtr = static_cast<const unsigned char*>(ptr);
	// while we haven't written total bytes
	while (byteCounter < (size * nmemb)) {
	   // get character to be written
		char cint = *buffPtr;
		// if we reached EOF, return EOF
		if (cint == EOF) {
			stream->eof = true;
			return EOF;
		}
		// write the cahracter using fputc
		int writtenChar = fputc(cint, stream);
		// increment byteCounter by size of char
		byteCounter += sizeof((char) writtenChar);
		// increment buffPtr
		buffPtr++;
	}
	// calculate number of items successfully added to buffer
	int itemsWritten = byteCounter / size;
	// return number of items successfully added to buffer
	return itemsWritten;
}

// Description: reads a character string from a file stream
// Pre-condition: pointer to string object, corresponding size, and stream to read from
// Post-condition: returns newly filled string from
char *fgets(char *str, int size, FILE *stream)
{
	// make copy of strCopy
	char *strCopy = str;
	// get max bytes or up to new line
	for (int i = size; size > 0; size--) {
	   // get character
	   int c = fgetc(stream);
	   // if characther is eof, break 
		if (c  == EOF) {
			break;
		}
      // store character into string copy 
		*strCopy = c;
		// increment string copy
		strCopy++;
		// if character is new line, break, no need to keep going
		if (c == '\n') {
			break;
		}
	}
   // if strCopy is the same as original str, nothing was added, so return nullptr
	*strCopy = 0;
	if (strCopy == str) {
		return nullptr;
	}
   // otherwise, return strCopy containing new character(s)
	return strCopy;
}

// Description: writes a character string to a file stream
// Pre-condition: accepts the string to write and target stream
// Post-condition: If successful, it will return a non-negative number. Else, it will return EOF error.
int fputs(const char *str, FILE *stream)
{
	if (str == nullptr) {
		return EOF;
	} else {
      // send to fwrite
		int bytesWritten = fwrite(str, strlen(str), 1, stream);
		// if nothing written, it was unsuccessful, and return EOF
		if (bytesWritten <= 0) {
		   return EOF;
		}
		// return bytes written
		return bytesWritten;
	}
}

// Description: moves the file position to a specific location in a file
// Pre-condition: accepts stream,  number of bytes to offset from origin, and origin reference
// Post-condition: returns 0 if successful, else it returns -1.
int fseek(FILE *stream, long offset, int whence)
{		
	if (whence != SEEK_CUR && whence != SEEK_SET && whence != SEEK_END ) {
		return -1;
   }
	// flush stream
	fflush(stream);
	// set stream end of as false if it didn't return -1
	stream->eof = false;
	// call lseek system call
	int seekLoc = lseek(stream->fd, offset ,whence);
	// if there was an error
	if(seekLoc == -1) {
		return -1;
	}
	// if successful 
	return 0;
}

// Description: checks for the end-of-file
// Pre-condition: accepts stream
// Post-condition: returns non-zero value when eof indicator associated with stream is set, else returns 0.
int feof(FILE *stream)
{
	return stream->eof;
}

// Description: flushes, closes, and deletes stream. 
// Pre-condition: accepts stream to be closed
// Post-condition: returns 0 if successful
int fclose(FILE *stream)
{
	// flush any unwritten output from the buffer to the file
	fflush(stream);
	// close stream
	close(stream->fd);
	// deallocate stream
	delete stream;
	// return 0;
	return 0;
}
