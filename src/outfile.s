	.global _blob
	.global _blob_size
_blob:
	.incbin "outfile.in"
1:
_blob_size:
	.int 1b - _blob
