# from PIL import ImageGrab
import pyautogui
from time import sleep

class lab4:
	def __init__(self):
		self.coordinates = {
			'time': ((1305, 328), (1437, 358)),
			'mass': ((1395, 391), (1320, 391)),
			'radius': ((1395, 450), (1320, 450)),
			'height': ((1395, 506), (1320, 506)),
			'start': (1420, 569),
			'stop': (1420, 623),
			'reset': (1420, 679),
			'googleedit': (674, 275),
		}

	# def get_screen(self, rect):
	# 	return ImageGrab.grab(rect)

	def click(self, coords):
		pyautogui.moveTo(coords)
		sleep(0.1)
		pyautogui.click()
		sleep(0.1)

	def press(self, *keys):
		pyautogui.hotkey(*keys, interval=0.1)
		sleep(0.1)

	def highlight(self, rect):
		pyautogui.moveTo(rect[0][0], rect[0][1])
		sleep(0.5)
		pyautogui.dragTo(rect[1][0], rect[1][1])
		sleep(0.1)

	def erase(self, rect):
		self.highlight(rect)
		self.press('backspace')

	def copy(self, rect):
		self.highlight(rect)
		self.press('ctrl', 'c')

	def write(self, string):
		for char in string:
			self.press(char)

	def save(self, newcolumn=False, newgroup=False):
		self.press('ctrl', 'shift', 'tab')
		self.press('ctrl', 'v')

		self.press('enter')
		self.press('backspace')
		self.press('backspace')
		self.press('backspace')
		self.press('home')
		self.press('delete')
		self.press('delete')

		self.press('enter')

		if newcolumn:
			self.press('right')
			for _ in range(5):
				self.press('up') 

		if newgroup:
			self.press('down')
			for _ in range(5):
				self.press('left')

		self.press('ctrl', 'tab')

	def solve(self):
		self.erase(self.coordinates['height'])
		self.write('0.7')

		masses = ['0.1', '0.3', '0.6', '0.9']
		radiuses = ['0.07', '0.1', '0.13', '0.16', '0.19', '0.22']
		sleeps = [
			[10, 12, 14, 16, 17.5, 21],
			[4.5, 5.5, 6.5, 7.5, 9, 10],
			[3.2, 4.2, 4.5, 5.3, 6, 6.8],
			[2.6, 3.2, 3.7, 4.3, 4.8, 5.5]
		]

		for m, mass in enumerate(masses):
			self.erase(self.coordinates['mass'])
			self.write(mass)

			for h, radius in enumerate(radiuses):
				self.erase(self.coordinates['radius'])
				self.write(radius)


				for i in range(5):
					self.click(self.coordinates['start'])
					sleep(sleeps[m][h])

					self.copy(self.coordinates['time'])
					self.save(newcolumn=(i == 4 and radius != radiuses[-1]),
							  newgroup=(radius == radiuses[-1] and i == 4))

					self.click(self.coordinates['reset'])


if __name__ == '__main__':
	laba = lab4()
	sleep(3)
	laba.solve()




