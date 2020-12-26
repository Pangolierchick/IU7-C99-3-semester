import tkinter as tk
from tkinter import ttk
from sys import exit
from tkinter import messagebox
import arraylib as ar
from interface_literals import *

def check_input(input:str) -> bool:
    for i in input.split():
        try:
            int(i)
        except Exception as e:
            return False
    return True
        

class rootWindow():
    root_window = None
    
    array_input = None
    shift_input = None
    output = None

    def __init__(self) -> None:
        self.window()

    def window(self) -> None:
        """
        Creates main window
        """
        
        self.root_window = tk.Tk()

        self.root_window.title("Работа с массивом")
        self.root_window.minsize(WINDOW_SIZE[0], WINDOW_SIZE[1])

        array_label = tk.Label(self.root_window, text=ARRAY_LABEL_TEXT)
        array_label.grid(row=0, column=0)

        output_label = tk.Label(self.root_window, text=OUTPUT_LABEL_TEXT)
        output_label.grid(row=1, column=0)

        self.array_input = tk.Entry(self.root_window)
        self.array_input.grid(row=0, column=1)

        shift_label = tk.Label(self.root_window, text=SHIFT_LABEL_TEXT)
        shift_label.grid(row=0, column=2)

        self.shift_input = tk.Spinbox(self.root_window, from_=0, to=10)
        self.shift_input.grid(row=0, column=3)

        self.output = tk.Label(self.root_window, bg=OUTPUT_COLOR, text=' ' * 20)
        self.output.grid(row=1, column=1)

        exit_button = tk.Button(self.root_window, text=EXIT_BUTTON_TEXT)
        exit_button.grid(row=3, column=0)
        exit_button.bind("<Button-1>", self.exit_button)

        find_sqrs_button = tk.Button(self.root_window, text=FIND_NONSQRS_TEXT)
        find_sqrs_button.grid(row=3, column=1)
        find_sqrs_button.bind("<Button-1>", self.find_sqrs_button)
        
        shift_button = tk.Button(self.root_window, text=SHIFT_BTN_TEXT)
        shift_button.grid(row=3, column=2)
        shift_button.bind("<Button-1>", self.shift_button)


        self.root_window.mainloop()
    
    def exit_button(self, *args):
        if messagebox.askokcancel("Выйти?", EXIT_CONFIRMATION_MSG):
            exit(0)

    def find_sqrs_button(self, *args):
        if not check_input(self.__get_arr_input()):
            messagebox.showerror("Неправильный ввод", INPUT_ERROR_MSG)
        else:
            src = [int(i) for i in self.__get_arr_input().split()]

            new_list = ar.nonsqr(src)
            self.output['text'] = ' '.join(map(str, new_list))
    
    def shift_button(self, *args):
        if not check_input(self.__get_arr_input()) or not check_input(self.__get_shift_input()):
            messagebox.showerror("Неправильный ввод", INPUT_ERROR_MSG)
        else:
            src = [int(i) for i in self.__get_arr_input().split()]
            shift = int(self.__get_shift_input())

            new_list = ar.left_shift(src, shift)
            self.output['text'] = ' '.join(map(str, new_list))
    
    def __get_arr_input(self):
        return self.array_input.get()

    def __get_shift_input(self):
        return self.shift_input.get()
