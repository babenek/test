from pathlib import Path

if __name__ == """__main__""":
    p = Path("test") / "1" / "2"
    assert str(p) == "test/1/2", p
