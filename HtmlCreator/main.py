import os
import tkinter as tk
import tkinter.ttk as ttk
from tkinter import simpledialog


htmlTags = (
    "div",
    "p",
    "a",
    "h1", "h2", "h3", "h4", "h5", "h6",
)

class Header:
    def __init__(self, master):
        self.master = master
        self.headerFrame = tk.Frame(self.master, relief=tk.RAISED, bd=2, bg="white")

        self.iconPath = tk.StringVar()
        self.iconPicker = ttk.Combobox(self.headerFrame, width=15, textvariable=self.iconPath)
        self.iconPicker['values'] = self.getIcons()
        self.iconPicker.current(0)

        self.addBtn = tk.Button(self.headerFrame, text="Add", command=self.addHeaderField)
        self.removeBtn = tk.Button(self.headerFrame, text="Remove", command=self.removeHeaderField)
        self.fieldFrame = tk.Frame(self.headerFrame, relief=tk.FLAT, bd=2, bg="white")
        self.headerFields = []
        self.maxHeaderFields = 4

        self.headerFrame.pack(side="top", anchor="w", fill="x")
        self.iconPicker.pack(side="left", padx=5, pady=5)
        self.removeBtn.pack(side="right", padx=5, pady=5)
        self.addBtn.pack(side="right", padx=5, pady=5)
        self.fieldFrame.pack(side="right", padx=5, pady=5)

    def getIcons(self):
        icons = []
        for file in os.listdir():
            if file.endswith(".png") or file.endswith(".jpg"):
                icons.append(str(file))
        return icons

    def addHeaderField(self):
        if len(self.headerFields) < self.maxHeaderFields:
            field = tk.Entry(self.fieldFrame, bg="grey")
            field.insert(10, f"Field {len(self.headerFields)+1}")
            self.headerFields.append(field)
            field.pack(side="left", padx=5, pady=5)

    def removeHeaderField(self):
        if len(self.headerFields) > 0:
            field = self.headerFields.pop()
            field.destroy()


class Window:
    def __init__(self, master):
        self.master = master
        self.header = Header(self.master)

        self.mainBody = ttk.Treeview(self.master, columns="content", height=20)
        self.mainBody.pack(padx=5, pady=5, fill="x")

        self.mainBody.heading("#0", text="HTML Tag")
        self.mainBody.heading("content", text="Content")

        button = ttk.Button(self.master, text="Add Element", command=self.addElement)
        button.pack(side="left", padx=5, pady=10)
        button = ttk.Button(self.master, text="Remove Element", command=self.removeElement)
        button.pack(side="left", padx=5, pady=10)
        button = ttk.Button(self.master, text="Edit selected", command=self.editElement)
        button.pack(side="left", padx=5, pady=10)
        button = ttk.Button(self.master, text="Move down", command=lambda: self.shiftElement("down"))
        button.pack(side="right", padx=5, pady=10)
        button = ttk.Button(self.master, text="Move up", command=lambda: self.shiftElement("up"))
        button.pack(side="right", padx=5, pady=10)
        button = ttk.Button(self.master, text="Compile", command=self.compileHTML)
        button.pack(side="bottom", padx=5, pady=10)

    def addElement(self):
        parentElement = self.mainBody.selection()
        print(parentElement)
        if len(parentElement) < 1:
            parentElement = ""
        else:
            parentElement = parentElement[0]
        if self.mainBody.item(parentElement)["text"] != "div" and self.mainBody.item(parentElement)["text"] != "":
            return
        popup = tk.Toplevel(self.master, padx=20, pady=20)
        popup.geometry("%dx%d%+d%+d" % (300, 200, 250, 125)) #width, height, x,y
        popup.title("Add Element")

        tag = tk.StringVar()
        tagFrame = tk.Frame(popup, relief=tk.FLAT, bd=2)
        tagFrame.pack(side="top")
        tagPicker = ttk.Combobox(tagFrame, width=40, textvariable=tag)
        tagPicker['values'] = htmlTags
        tagPicker.current(0)
        tagLabel = tk.Label(tagFrame, text="HTML tag")
        tagLabel.pack(side="left", padx=5, pady=5)
        tagPicker.pack(side="left", padx=5, pady=5)

        content = tk.StringVar()
        contentFrame = tk.Frame(popup, relief=tk.FLAT, bd=2)
        contentFrame.pack(side="top")
        contentField = ttk.Entry(contentFrame, width=40)
        contentLabel = tk.Label(contentFrame, text="Content")
        contentLabel.pack(side="left", padx=5, pady=5)
        contentField.pack(side="left", padx=5, pady=5)

        submitBtn = tk.Button(popup, text="Submit", command=lambda: content.set(contentField.get()))
        submitBtn.pack(side="top")
        submitBtn.wait_variable(content)

        self.mainBody.insert(parentElement, tk.END, text=tag.get(), values=([content.get()]))
        self.clearFocus(self)
        popup.destroy()

    def removeElement(self):
        element = self.mainBody.selection()[0]
        if (element != ""):
            self.mainBody.delete(element)

    def editElement(self):
        element = self.mainBody.selection()
        if len(element) < 1:
            return
        element = element[0]
        if self.mainBody.item(element)["text"] == "":
            return
        popup = tk.Toplevel(self.master, padx=20, pady=20)
        popup.geometry("%dx%d%+d%+d" % (300, 200, 250, 125))  # width, height, x,y
        popup.title("Add Element")

        tag = tk.StringVar()
        tagFrame = tk.Frame(popup, relief=tk.FLAT, bd=2)
        tagFrame.pack(side="top")
        tagPicker = ttk.Combobox(tagFrame, width=40, textvariable=tag)
        tagPicker['values'] = htmlTags
        tagPicker.current(htmlTags.index(self.mainBody.item(element)["text"]))
        tagLabel = tk.Label(tagFrame, text="HTML tag")
        tagLabel.pack(side="left", padx=5, pady=5)
        tagPicker.pack(side="left", padx=5, pady=5)

        content = tk.StringVar()
        contentFrame = tk.Frame(popup, relief=tk.FLAT, bd=2)
        contentFrame.pack(side="top")
        contentField = ttk.Entry(contentFrame, width=40)
        contentField.insert(10, self.mainBody.item(element)["values"][0])
        contentLabel = tk.Label(contentFrame, text="Content")
        contentLabel.pack(side="left", padx=5, pady=5)
        contentField.pack(side="left", padx=5, pady=5)

        submitBtn = tk.Button(popup, text="Submit", command=lambda: content.set(contentField.get()))
        submitBtn.pack(side="top")
        submitBtn.wait_variable(content)

        self.mainBody.item(element, text=tag.get(), values=([content.get()]))
        self.clearFocus(self)
        popup.destroy()


    def shiftElement(self, dir):
        if dir == "up":
            childElements = self.mainBody.selection()
            for i in childElements:
                self.mainBody.move(i, self.mainBody.parent(i), self.mainBody.index(i) - 1)
        else:
            childElements = self.mainBody.selection()
            for i in reversed(childElements):
                self.mainBody.move(i, self.mainBody.parent(i), self.mainBody.index(i) + 1)

    def compileHTML(self):
        f = open('myWebpage.html', 'w')
        f.close()
        f = open('myWebpage.html', 'a')
        f.write("<html>\n")

        f.write("<head>\n")#start header
        f.write("<div>\n")
        f.write(f"<img src={self.header.iconPath.get()} alt=icon width=50 height=50>")
        for link in self.header.headerFields:
            f.write(f"<a href=#{link.get()}>{link.get()}</a>\n")
        f.write("</div>\n")
        f.write("</head>\n") #end header

        f.write("<body>\n")
        for element in self.mainBody.get_children():
            item = self.mainBody.item(element)
            if item['text'] == "div":
                self.printSubElements(f, element)
            else:
                f.write(f"<{item['text']}> {item['values'][0]} </{item['text']}>\n")
        f.write("</body>\n")
        f.write("</html>")
        f.close()

    def printSubElements(self, f, element):
        item = self.mainBody.item(element)
        f.write(f"<{item['text']} style=\"{item['values'][0]}\">\n")
        for subElement in self.mainBody.get_children(element):
            subItem = self.mainBody.item(subElement)
            if subItem['text'] == "div":
                self.printSubElements(f, subElement)
            else:
                f.write(f"<{subItem['text']} style=\"display: inline-block;padding-left: 100px;\"> {subItem['values'][0]} </{subItem['text']}>\n")
        f.write(f"</{item['text']}>\n")


    def clearFocus(self, window):
        for i in self.mainBody.selection():
            self.mainBody.selection_remove(i)


root = tk.Tk()
root.title("HTML Builder")
root.geometry("800x600")
root.columnconfigure(0,weight=1)
root.rowconfigure(0,weight=1)
window = Window(root)
window.mainBody.bind("<Button-1>", window.clearFocus)
root.mainloop()