#!/usr/bin/python3
"""Define my square """


class Square:
    """My Private instance attribute """

    def __init__(self, size = 0):
        """Instantiation with optional """

        if not isinstance(size, int):
            raise TypeError("size must be an integer")
        elif size < 0:
            raise ValueError("size must be >= 0")
        self.__size = size

    @property
    def size(self):
        """
        property def size(self):
        to retrieve it
        """

        return self.__size

    @size.setter
    def size(self, value):
        """
        Private instance
        attribute
        """

        if not isinstance(value, int):
            raise TypeError("size must be an integer")
        elif value < 0:
            raise ValueError("size must be >= 0")
        self.__size = value

    def area(self):
        """Public instance method """

        return (self.__size ** 2)