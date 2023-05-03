#ifndef SPIFFSCHECKSUM_H
#define SPIFFSCHECKSUM_H

struct {
	const char* name;
	uint32_t sum;
} static const SPIFFSChecksums[] = {
		{ "/Dir/File.raw", 123456 }
};

#endif //SPIFFSCHECKSUM_H
