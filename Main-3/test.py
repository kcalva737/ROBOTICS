def encode(pin,value):
    myString = ord('#')<<16
    myString |= pin<<10
    myString |= value
    #myString = bin(bytes(myString,'utf-8') | ord('#')<<(4*4) )# & bin(0xffffff)
    #myString = myString | (pin<<(10)
    #myString = myString | (value)
    # 0000 0000-0000 00 00-00 0000 0000
    # 
    val1 = chr( (myString & 0xff0000) >> 16)
    val2 = chr( (myString & 0x00ff00) >> 8)
    val3 = chr(myString & 0x0000ff)
    
    return val1  + val2 + val3

pin = 10
value = 1000

#myStr = encode(pin,value);
#b = bytes('A','utf-8')
b = bin(ord('#'))
print( b )
print(encode(63,1023))