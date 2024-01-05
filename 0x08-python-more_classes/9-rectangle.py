#!/usr/bin/python3
"""
Create a new class Rectangle
"""


class Rectangle:
	"""class Rectangle"""
	number_of_instances = 0
	print_symbol = "#"

	def __init__(self, width=0, height=0):
		"""Initialize our rectangle"""
		self.height = height
		self.width = width
		Rectangle.number_of_instances += 1

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
		return self.__height * self.__width

	def perimeter(self):
		"""the perimeter of this rectangle"""
		if self.__width == 0 or self.__height == 0:
			return 0
		return ((self.__width + self.__height) * 2)

	def __str__(self):
		"""Return a string representation of the rectangle"""
		if self.__width == 0 or self.__height == 0:
			return ""
		rectangle = ""
		for i in range(self.__height):
			for x in range(self.__width):
				try:
					rectangle += str(self.print_symbol)
				except Exception:
					rectangle += type(self).print_symbol
			if i < self.__height - 1:
				rectangle += "\n"
		return rectangle

	def __repr__(self):
		"""Return a string representation of the rectangle for eval()"""
		return "Rectangle({:d}, {:d})".format(self.__width, self.__height)

	def __del__(self):
		"""Destructor method to print a message when an instance is deleted"""
		print("Bye rectangle...")
		Rectangle.number_of_instances -= 1

	@staticmethod
	def bigger_or_equal(rect_1, rect_2):
		"""Static method to compare rectangles based on area"""
		if not isinstance(rect_1, Rectangle):
			raise TypeError("rect_1 must be an instance of Rectangle")
		if not isinstance(rect_2, Rectangle):
			raise TypeError("rect_2 must be an instance of Rectangle")
		if rect_2.area() > rect_1.area():
			return rect_2
		return rect_1

	@classmethod
	def square(cls, size=0):
		"""Class method to create a square instance"""
		return cls(size, size)
