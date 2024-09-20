import tkinter as tk
from tkinter import filedialog, messagebox

class Assembler:
    def __init__(self):
        self.optab = {}
        self.symtab = {}
        self.intermediate_file = []
        self.machine_code = []

    def load_optab(self, optab_file):
        with open(optab_file, 'r') as f:
            for line in f:
                mnemonic, opcode = line.strip().split()
                self.optab[mnemonic] = opcode

    def pass1(self, input_file):
        locctr = 0
        with open(input_file, 'r') as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith(';'):  # Ignore empty lines and comments
                    continue
                
                label, mnemonic, operand = self.parse_line(line)
                
                if label:
                    self.symtab[label] = locctr
                
                if mnemonic in self.optab:
                    self.intermediate_file.append(f"{locctr:04X} {line}")
                    locctr += 1  # Increment for every instruction
                
                elif mnemonic == 'WORD':
                    self.intermediate_file.append(f"{locctr:04X} {line}")
                    locctr += 3  # WORD occupies 3 bytes
                
                elif mnemonic == 'RESW':
                    self.intermediate_file.append(f"{locctr:04X} {line}")
                    locctr += int(operand) * 3  # Reserve words (3 bytes each)
                
                elif mnemonic == 'RESB':
                    self.intermediate_file.append(f"{locctr:04X} {line}")
                    locctr += int(operand)  # Reserve bytes
                
                elif mnemonic == 'BYTE':
                    self.intermediate_file.append(f"{locctr:04X} {line}")
                    locctr += len(operand) - 3  # BYTE allocation depends on operand size
    
    def pass2(self):
        for line in self.intermediate_file:
            locctr, instr = line.split(maxsplit=1)
            label, mnemonic, operand = self.parse_line(instr)
            if mnemonic in self.optab:
                opcode = self.optab[mnemonic]
                address = self.symtab.get(operand, '0000')  # Default 0000 if operand not found
                self.machine_code.append(f"{opcode}{address}")
    
    def parse_line(self, line):
        parts = line.split()
        if len(parts) == 3:
            return parts[0], parts[1], parts[2]
        elif len(parts) == 2:
            return None, parts[0], parts[1]
        elif len(parts) == 1:
            return None, parts[0], None
        return None, None, None


class AssemblerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Two-Pass Assembler")

        self.assembler = Assembler()

        self.optab_label = tk.Label(root, text="Load OPTAB file:")
        self.optab_label.pack()

        self.optab_button = tk.Button(root, text="Browse", command=self.load_optab)
        self.optab_button.pack()

        self.input_label = tk.Label(root, text="Load Assembly Input file:")
        self.input_label.pack()

        self.input_button = tk.Button(root, text="Browse", command=self.load_input)
        self.input_button.pack()

        self.assemble_button = tk.Button(root, text="Assemble", command=self.assemble)
        self.assemble_button.pack()

        self.result_label = tk.Label(root, text="Results:")
        self.result_label.pack()

        self.result_text = tk.Text(root, height=10, width=50)
        self.result_text.pack()

    def load_optab(self):
        optab_file = filedialog.askopenfilename(title="Select OPTAB file", filetypes=[("Text Files", "*.txt")])
        if optab_file:
            self.assembler.load_optab(optab_file)
            messagebox.showinfo("Success", "OPTAB loaded successfully!")

    def load_input(self):
        self.input_file = filedialog.askopenfilename(title="Select Assembly Input file", filetypes=[("Text Files", "*.txt")])
        if self.input_file:
            messagebox.showinfo("Success", "Input file loaded successfully!")

    def assemble(self):
        if hasattr(self, 'input_file'):
            self.assembler.pass1(self.input_file)
            self.assembler.pass2()

            # Show intermediate file and machine code
            self.result_text.delete(1.0, tk.END)
            self.result_text.insert(tk.END, "Intermediate File:\n")
            self.result_text.insert(tk.END, "\n".join(self.assembler.intermediate_file) + "\n\n")

            self.result_text.insert(tk.END, "Machine Code:\n")
            self.result_text.insert(tk.END, "\n".join(self.assembler.machine_code))

            messagebox.showinfo("Success", "Assembly completed!")
        else:
            messagebox.showerror("Error", "Please load an input file first!")


if __name__ == "__main__":
    root = tk.Tk()
    gui = AssemblerGUI(root)
    root.mainloop()
