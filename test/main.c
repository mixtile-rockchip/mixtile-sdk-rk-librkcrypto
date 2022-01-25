/*
 * Copyright (c) 2022 Rockchip Electronics Co. Ltd.
 */
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "test_otp_key_crypto.h"
#include "test_cipher.h"
#include "test_crypto_mem.h"
#include "test_hash.h"

enum {
	OPTION_TOP = 0,
	ALL,
	CIPHER,
	HASH,
	HMAC,
	SETKEY,
	OTPKEY,
	MEM,
	THROUGHPUT,
	OPTION_BUTT,
};

static void guide(void)
{
	printf("\n######## rkcrypto api test ########\n");
	printf("%s\n", RK_CRYPTO_API_FULL_VERSION);

	printf("Entry one parameter as follow:\n");
	printf("\t-all           Function of all ciphers\n");
	printf("\t-cipher        Function of cipher\n");
	printf("\t-hash          Function of hash\n");
	printf("\t-hmac          Function of hmac\n");
	printf("\t-setkey        Function of setkey. NOTE: it will write key to OTP area.\n");
	printf("\t-otpkey        Function of otpkey\n");
	printf("\t-mem           Maximum buffer size requested by crypto mem alloc, test until alloc failed\n");
	printf("\t-throughput    Throughput of all ciphers, MB/s\n");
}

int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	static struct option long_options[] = {
		{"all",		0,	NULL,	ALL},
		{"cipher",	0,	NULL,	CIPHER},
		{"hash",	0,	NULL,	HASH},
		{"hmac",	0,	NULL,	HMAC},
		{"setkey",	0,	NULL,	SETKEY},
		{"otpkey",	0,	NULL,	OTPKEY},
		{"mem",		0,	NULL,	MEM},
		{"throughput",	0,	NULL,	THROUGHPUT},
		{NULL,		0,	NULL,	0},
	};

	if (argc < 2)
		guide();

	while ((opt = getopt_long_only(argc, argv, "", long_options, &option_index)) != -1) {
		switch (opt) {
		case ALL:
			test_cipher();
			test_hash();
			test_hmac();
			test_write_otp_key();
			test_otp_key();
			test_crypto_mem();
			break;
		case CIPHER:
			test_cipher();
			break;;
		case HASH:
			test_hash();
			break;
		case HMAC:
			test_hmac();
			break;
		case SETKEY:
			test_write_otp_key();
			break;
		case OTPKEY:
			test_otp_key();
			break;
		case MEM:
			test_crypto_mem();
			break;
		case THROUGHPUT:
			test_speed_otp_key_cipher(100);
			break;
		case '?':
			guide();
			break;
		default:
			break;
		}

	}

	printf("\n######## Test done ########\n");

	return 0;
}
