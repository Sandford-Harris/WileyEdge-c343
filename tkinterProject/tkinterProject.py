import tkinter as tk
from tkinter import colorchooser
from tkinter import ttk
from PIL import Image

from Line import *
from Rect import *

window = tk.Tk()
window.wm_title("like Paint but bad")
window.rowconfigure(1,weight=1) # fill the rest of the space with the canvas row
window.columnconfigure(0,weight=1) # make items resize with window width too

doLine = False
doErase = False
doRect = False
objects = []
obj = None

objectsAdded = []
# default object params
colour = "black"
lineWidth = 1
fillShape = tk.IntVar()


def undo(event):
    if len(objectsAdded) > 0:
        lastObject = objectsAdded.pop()
        if lastObject == "line" and len(objects) > 0:
            lastLine = objects.pop()
            for line_part in lastLine:
                canvas.delete(line_part)
        elif lastObject == "rect":
            lastobj = objects.pop()
            canvas.delete(lastobj)


def getColour():
    global colour
    pickedCol = colorchooser.askcolor(title="Choose color")
    if pickedCol[0] is not None and pickedCol[1] is not None:
        colour = pickedCol[1]
        #ensuring text is always readable by checking brightness of new bg colour
        colBrightness = 0.2126 * pickedCol[0][0] + 0.7152 * pickedCol[0][1] + 0.0722 * pickedCol[0][2]
        fg = "black"
        if colBrightness < 40:
            fg = "white"
        colourBtn.configure(bg=colour, fg=fg)


def updateWidth(event):
    global lineWidth
    lineWidth = widthSlider.get()


def toggleLineDraw():
    global doLine
    if not doLine:
        resetButtons()
        canvas.bind('<Button-1>', draw_line)
        canvas.bind('<B1-Motion>', draw_line)
        canvas.bind('<ButtonRelease-1>', draw_line)
        drawLineBtn['relief'] = tk.SUNKEN
        doLine = True
    else:
        resetButtons()

def draw_line(event):
    global obj
    if obj is None:
        obj = Line(lineWidth, colour)
    if event.type == tk.EventType.ButtonPress:
        obj.set_start(canvas, event)
    elif event.type == tk.EventType.Motion:
        obj.draw_line(canvas, event)
    elif event.type == tk.EventType.ButtonRelease:
        obj.set_end(canvas, event)
        objects.append(obj.parts)
        objectsAdded.append("line")
        del obj
        obj = None

def toggleErase():
    global doErase
    if not doErase:
        resetButtons()
        canvas.bind('<Button-1>', erase)
        canvas.bind('<B1-Motion>', erase)
        canvas.bind('<ButtonRelease-1>', erase)
        eraseBtn['relief'] = tk.SUNKEN
        doErase = True
    else:
        resetButtons()

def erase(event):
    global obj
    if obj is None:
        obj = Line(lineWidth, "white")
    if event.type == tk.EventType.ButtonPress:
        obj.set_start(canvas, event)
    elif event.type == tk.EventType.Motion:
        obj.draw_line(canvas, event)
    elif event.type == tk.EventType.ButtonRelease:
        objects.append(obj.parts)
        objectsAdded.append("line")
        del obj
        obj = None


def toggleRectDraw():
    global doRect
    if not doRect:
        resetButtons()
        canvas.bind('<Button-1>', draw_rect)
        canvas.bind('<B1-Motion>', draw_rect)
        canvas.bind('<ButtonRelease-1>', draw_rect)
        drawRectBtn['relief'] = tk.SUNKEN
        doRect = True
    else:
        resetButtons()

def draw_rect(event):
    global obj
    if obj is None:
        obj = Rect(lineWidth, colour, fillShape)
    if event.type == tk.EventType.ButtonPress:
        obj.set_start(canvas, event)
    elif event.type == tk.EventType.Motion:
        obj.draw(canvas, event)
    elif event.type == tk.EventType.ButtonRelease:
        obj.set_end(event)
        objects.append(obj)
        objectsAdded.append("rect")
        del obj
        obj = None


def resetButtons():
    global doLine
    global doErase
    global doRect
    canvas.unbind('<Button-1>')
    canvas.unbind('<B1-Motion>')
    canvas.unbind('<ButtonRelease-1>')
    if doLine:
        drawLineBtn['relief'] = tk.RAISED
        doLine = False
    if doErase:
        eraseBtn['relief'] = tk.RAISED
        doErase = False
    if doRect:
        drawRectBtn['relief'] = tk.RAISED
        doRect = False

def saveImage():
    popup = tk.Toplevel(window)
    popup.wm_title("Save Image")
    textinp = ttk.Entry(popup, width=40)
    textinp.grid(row=0, column=0, sticky="ew")
    tk.Button(popup, text="Save", command=lambda: saveImageHelper(textinp.get(), popup))\
        .grid(row=1, column=0, sticky="ew")


def saveImageHelper(filename, popup):
    if filename != "":
        #REQUIRES GHOSTSCRIPT INSTALLED TO WORK
        canvas.postscript(file=filename + '.eps')
        img = Image.open(filename + '.eps')
        img.save(filename + '.png', 'png')
    popup.destroy()


buttonFrame = tk.Frame(window, relief=tk.RAISED, bd=2)
drawLineBtn = tk.Button(buttonFrame, text="Draw line", command=toggleLineDraw)
drawRectBtn = tk.Button(buttonFrame, text="Draw rectangle", command=toggleRectDraw)
eraseBtn = tk.Button(buttonFrame, text="Erase", command=toggleErase)
colourBtn = tk.Button(buttonFrame, text="change colour", bg="black", fg="white", command=getColour)
fillShapeBtn = tk.Checkbutton(buttonFrame, text="Fill Shape", variable=fillShape)
SliderFrame = tk.Frame(buttonFrame, relief=tk.FLAT, bd=2)
SliderLabel = tk.Label(SliderFrame, text="Line width")
widthSlider = tk.Scale(SliderFrame, from_=1, to=20, orient=tk.HORIZONTAL, command=updateWidth)
saveBtn = tk.Button(buttonFrame, text="Save Image", command=saveImage)

drawLineBtn.grid(row=0, column=0, sticky="ew", padx=5, pady=5)
drawRectBtn.grid(row=0, column=1, sticky="ew", padx=5, pady=5)
eraseBtn.grid(row=0, column=2, sticky="ew", padx=5, pady=5)
colourBtn.grid(row=0, column=3, sticky="ew", padx=5, pady=5)
fillShapeBtn.grid(row=0, column=4, sticky="ew", padx=5, pady=5)
SliderFrame.grid(row=0, column=5, sticky="ew", padx=5)
SliderLabel.grid(row=0, column=0, sticky="ns", padx=5)
widthSlider.grid(row=1, column=0, sticky="ns", padx=5)
saveBtn.grid(row=0, column=6, sticky="w", padx=5, pady=5)
buttonFrame.grid(row=0, column=0, sticky="new")

canvas = tk.Canvas(bg="white", width=600, height=400)
canvas.grid(row=1, column=0, sticky="nsew")
window.bind('<Control-z>', undo)



window.mainloop()