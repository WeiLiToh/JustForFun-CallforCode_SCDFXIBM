#!/usr/bin/env python3

from Crypto.Util.number import getPrime, inverse, bytes_to_long, long_to_bytes

e = 3
d = -1

n = 742449129124467073921545687640895127535705902454369756401331
print(len(n))

# n will be 8 * (100 + 100) = 1600 bits strong which is pretty good
while d == -1:
    p = getPrime(100)
    q = getPrime(100)

    phi = (p - 1) * (q - 1)
    d = inverse(e, phi)


flag = b"XXXXXXXXXXXXXXXXXXXXXXX"
pt = bytes_to_long(flag)
ct = pow(pt, e, n)

print(f"n = {n}")
print(f"e = {e}")
print(f"ct = {ct}")

pt = pow(ct, d, n)
decrypted = long_to_bytes(pt)

print(decrypted)



