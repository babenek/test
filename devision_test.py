#!/usr/bin/env python3

import sys
import random

def dice():
    a=10+random.randrange(89)
    b=10+random.randrange(89)
    z=random.randrange(a-1) if (a<b) else random.randrange(b-1)
    c=z+a*b
    print("\n{} : {} =".format(c,b))
    #print("\n{} : {} = {} + {}".format(c,b,a,z))
    return a,z

def test():
    s=''
    while(s != 'stop'):
        res,rem = dice();
        while True:
            try:
                a=int(input('4ACTKA='))
                z=int(input('OCTA4A='))
            except KeyboardInterrupt:
                return 0
            except:
                continue
            
            if (a==res and z==rem):
                print('correct');
                break;
            else:
                print('wrong')
                continue
    return 0

if __name__ == '__main__':
    sys.exit(test())



