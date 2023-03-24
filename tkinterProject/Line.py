
class Line:
    def __init__(self, width=1, colour="black"):
        self.width = width
        self.points = []
        self.parts = []
        self.colour = colour
        self.id = None

    def set_start(self, canvas, event):
        self.points.extend((event.x, event.y))
        # draw a point
        start = self.poly_oval(canvas, event.x, event.y)
        self.parts.append(start)

    def draw_line(self, canvas, event):
        self.points.extend((event.x, event.y))
        if self.id is not None:
            canvas.delete(self.id)
        self.id = canvas.create_line(self.points, fill=self.colour, width=self.width)

    def set_end(self, canvas, event):
        self.parts.append(self.id)
        # draw a point
        self.points.extend((event.x, event.y))
        end = self.poly_oval(canvas, event.x, event.y)
        self.parts.append(end)

    #draws rounded ovals (unlike create_oval)
    def poly_oval(self, canvas, x, y, resolution=32):
        x -= self.width/2
        y -= self.width/2
        points = [x, y,
                  x + self.width, y,
                  x + self.width, y + self.width,
                  x, y + self.width,
                  x, y]
        return canvas.create_polygon(points, fill=self.colour, smooth=True, splinesteps=resolution)