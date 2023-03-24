class Rect:
    def __init__(self, width=1, colour="black", fill=False):
        self.width = width
        self.start_x = -1
        self.start_y = -1
        self.end_x = -1
        self.end_y = -1
        self.colour = colour
        self.fill = fill
        self.id = None

    def set_start(self, canvas, event):
        self.start_x = event.x
        self.start_y = event.y
        self.draw(canvas, event)

    def draw(self, canvas, event):
        if self.id is not None:
            canvas.delete(self.id)
        if self.fill.get():
            self.id = canvas.create_rectangle(self.start_x, self.start_y, event.x, event.y,
                                              fill=self.colour, outline=self.colour, width=self.width)
        else:
            self.id = canvas.create_rectangle(self.start_x, self.start_y, event.x, event.y,
                                              outline=self.colour, width=self.width)

    def set_end(self, event):
        self.end_x = event.x
        self.end_y = event.y
