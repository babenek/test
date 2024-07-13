from tkinter import *
from tkinter import filedialog


def main():
    window = Tk()
    window.title("hi")
    lbl = Label(window, text="Привіт")
    lbl.grid(column=0, row=0)
    window.geometry('400x250')
    lbl.grid(column=0, row=0)

    def clicked():
        files = filedialog.askopenfilenames()
        lbl.configure(text=", ".join(files))

    btn = Button(window, text="Не натискати!", command=clicked)
    btn.grid(column=1, row=0)
    window.mainloop()


if __name__ == "__main__":
    main()
