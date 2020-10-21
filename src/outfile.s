	.global _blob
	.global _blob_size
	.global _bufferh
	.global _bufferh_size
	.global _bufferc
	.global _bufferc_size
_blob:
	.incbin "outfile.in"
1:
_blob_size:
	.int 1b - _blob
_bufferh:
	.incbin "basebuffer.h"
2:
_bufferh_size:
	.int 1b- _bufferh
_bufferc:
	.incbin "basebuffer.c"
3:
_bufferc_size:
	.int 1b- _bufferc
