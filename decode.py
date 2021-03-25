from cayennelpp import LppFrame


# byte buffer in CayenneLPP format with 1 data item
# i.e. on channel 1, with a temperature of 25.5C
buffer = bytearray([0x01, 0x02, 0x01, 0xa8, 0x03, 0x68, 0x07,0x05, 0x67,0xfe,0x5b])
# create frame from bytes
frame = LppFrame().from_bytes(buffer)
# print the frame and its data
print(frame)