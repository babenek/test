import io
import tarfile


def main(filename):
    data = bytearray()
    with open(filename, 'rb') as f:
        data = f.read()

    with tarfile.TarFile(fileobj=io.BytesIO(data)) as tf:
        for tfi in tf.getmembers():
            # skip directory
            if not tfi.isreg():
                continue
            if tfi.size > 1 << 30:
                print("Quota reached")
                continue
            with tf.extractfile(tfi) as f:
                f_seek = f.seek(io.SEEK_END)
                f_tell = f.tell()
                if f_tell > 1 << 30:
                    print("Quota reached")
                    continue
                f.seek(io.SEEK_SET)
                d = f.read()
                print(len(d))


if __name__ == """__main__""":
    main("gnu-sparse-big.tar")
