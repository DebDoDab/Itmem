import bisect
from PIL import Image
import sys

WIDTH = 170
HEIGHT = 110

class Point:
    def __init__(self, x: float, y: float, value: float):
        self.x = x
        self.y = y
        self.value = value

    def __repr__(self):
        return str(self.x) + " " + str(self.y) + " " + str(self.value)

    def dist(self, x: float, y: float) -> float:
        return ((self.x - x)**2 + (self.y - y)**2)**0.5


class TensionField:
    def __init__(self, points: list):
        self.points = points

    def getMinX(self) -> float:
        return min(self.points, key=lambda point: point.x).x

    def getMaxX(self) -> float:
        return max(self.points, key=lambda point: point.x).x

    def getMinY(self) -> float:
        return min(self.points, key=lambda point: point.y).y

    def getMaxY(self) -> float:
        return max(self.points, key=lambda point: point.y).y

    def getTension(self, x: float, y: float) -> float:
        leftX = None
        rightX = None
        leftY = None
        rightY = None

        for point in self.points:
            if point.x < x and (leftX is None or leftX.dist(x, y) > point.dist(x, y)):
                leftX = point

            if point.x > x and (rightX is None or rightX.dist(x, y) > point.dist(x, y)):
                rightX = point

            if point.y < y and (leftY is None or leftY.dist(x, y) > point.dist(x, y)):
                leftY = point

            if point.y > y and (rightY is None or rightY.dist(x, y) > point.dist(x, y)):
                rightY = point

        if leftX is None:
            leftX = Point(0, 0, 0)

        if rightX is None:
            rightX = Point(0, 0, 0)

        if leftY is None:
            leftY = Point(0, 0, 0)

        if rightY is None:
            rightY = Point(0, 0, 0)

        ex = (leftX.value - rightX.value) / (leftX.x - rightX.x)
        ey = (leftY.value - rightY.value) / (leftY.y - rightY.y)

        return (ex**2 + ey**2)**0.5


class Img:
    def __init__(self):
        self.image = Image.new('HSV', (WIDTH * 5, HEIGHT * 5), (128, 255, 255))
        self.pixels = self.image.load()

    def save(self, fileName: str) -> None:
        self.image.show()
        self.image.convert('RGB').save(fileName)

    def setPixel(self, x: int, y: int, value: float) -> None:
        for i in range(5):
            for j in range(5):
                self.pixels[x * 5 + i, y * 5 + j] = (int(value * 127 + 128), 255, 255)


class Data:
    def __init__(self, fileName: str):
        self.points = None
        self.tf = None
        self.img = None
        self.getValues('data/' + fileName + '.txt')
        self.createImage()
        self.saveImage('imgs/' + fileName + '.png')

    def getValues(self, fileName: str) -> None:
        self.points = []
        with open(fileName, 'r') as inp:
            for line in inp:
                if line[0] == '%':
                    continue
                line = line.split(' ')
                line = [num for num in line if num != '']
                line[2] = line[2][:-1]
                if line[2][-1] == 'i':
                    value = line[2].replace('+', '-').split('-')[0]
                    if value[-1] == 'E':
                        value += line[2][len(value)] + line[2].replace('+', '-').split('-')[1]
                self.points.append(Point(float(line[0]), float(line[1]), float(value)))

        self.tf = TensionField(self.points)

    def createImage(self) -> None:
        self.img = Img()
        minX = self.tf.getMinX()
        maxX = self.tf.getMaxX()
        minY = self.tf.getMinY()
        maxY = self.tf.getMaxY()

        values = []
        valueList = []
        for y in range(HEIGHT):
            values.append([])
            print(round(y/HEIGHT*100, 2), '%')
            for x in range(WIDTH):
                value = self.tf.getTension(x / WIDTH * (maxX - minX) + minX,
                                           y / HEIGHT * (maxY - minY) + minY)
                values[-1].append(value)
                valueList.append(value)

        valueList.sort()
        minValue = valueList[0]
        maxValue = valueList[int(len(valueList) * 0.98)]

        for y in range(HEIGHT):
            for x in range(WIDTH):
                self.img.setPixel(x, y, (values[y][x] - minValue) / (maxValue - minValue))


    def saveImage(self, fileName: str) -> None:
        self.img.save(fileName)



if __name__ == '__main__':
    a = Data(sys.argv[1])





