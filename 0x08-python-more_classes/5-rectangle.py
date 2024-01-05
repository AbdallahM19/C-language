#!/usr/bin/python3
"""
Create a new class Rectangle
"""


class Rectangle:
	"""class Rectangle"""

	def __init__(self, width=0, height=0):
		"""Initialize our rectangle"""
		self.height = height
		self.width = width

	@property
	def width(self):
		"""get width attribute"""
		return self.__width

	@width.setter
	def width(self, value):
		"""setter width attribute"""
		if not isinstance(value, int):
			raise TypeError("width must be an integer")
		if value < 0:
			raise ValueError("width must be >= 0")
		self.__width = value

	@property
	def height(self):
		"""get height attribute"""
		return self.__height

	@height.setter
	def height(self, value):
		"""setter height attribute"""
		if not isinstance(value, int):
			raise TypeError("height must be an integer")
		if value < 0:
			raise ValueError("height must be >= 0")
		self.__height = value

	def area(self):
		"""area of the rectangle"""
		return (self.height * self.width)

	def perimeter(self):
		"""the perimeter of this rectangle"""
		if (self.width == 0 or self.height == 0):
			return 0
		return ((self.width + self.height) * 2)

	def __str__(self):
		"""Return a string representation of the rectangle"""
		if self.width == 0 or self.height == 0:
			return ""
		rectangle = ""
		for i in range(self.__height):
			for x in range(self.__width):
				rectangle += "#"
			if i < self.__height - 1:
				rectangle += "\n"
		return (rectangle)

	def __repr__(self):
		"""Return a string representation of the rectangle for eval()"""
		return ("Rectangle({:d}, {:d})".format(self.width, self.height))

	def __del__(self):
		"""Destructor method to print a message when an instance is deleted"""
		print("Bye rectangle...")
