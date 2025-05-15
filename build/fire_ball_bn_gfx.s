
@{{BLOCK(fire_ball_bn_gfx)

@=======================================================================
@
@	fire_ball_bn_gfx, 8x8@4, 
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2025-05-15, 05:44:41
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global fire_ball_bn_gfxTiles		@ 32 unsigned chars
	.hidden fire_ball_bn_gfxTiles
fire_ball_bn_gfxTiles:
	.word 0x00111100,0x01AAAB10,0x1AAAAAA1,0x1ABAABA1,0x1AAAAAA1,0x1AAAAAB1,0x01ABAA10,0x00111100

	.section .rodata
	.align	2
	.global fire_ball_bn_gfxPal		@ 32 unsigned chars
	.hidden fire_ball_bn_gfxPal
fire_ball_bn_gfxPal:
	.hword 0x0000,0x0000,0x2D28,0x6FDF,0x081B,0x1CD1,0x4A99,0x080D
	.hword 0x1EBB,0x1CA4,0x1977,0x0CF0,0x290C,0x0000,0x0000,0x0000

@}}BLOCK(fire_ball_bn_gfx)
