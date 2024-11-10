import binascii
import hashlib

text = '''The quick brown fox jumps over the lazy dog
Τhe quick brown fox jumps over the lazy dog
Тhe quick brown fox jumps over the lazy dog
'''

# tips for obfuscation
assert 'i' != 'і' and 'T' != 'Τ'

# Supported: md5 sha1 sha224 sha256 sha384 sha512 blake2b blake2s sha3_224 sha3_256 sha3_384 sha3_512
hash_function = hashlib.sha256
digest_size = len(hash_function(b'').digest())
result_digest = b'\0' * digest_size
lines = text.splitlines(keepends=False)
charset = set()
for line in lines:
    charset.update(set(line))
    data = line.encode('utf8')
    line_hash = hash_function(data)
    result_digest = bytes(a ^ b for a, b in zip(result_digest, line_hash.digest()))
    print(line_hash.hexdigest(), data)
result_hash_line = binascii.hexlify(result_digest).decode('ascii')
print('--' * digest_size)
print(result_hash_line, 'lines:', len(lines), 'chars:', len(charset))
