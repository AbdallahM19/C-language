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

    def area(self):
        """Public instance method """

        return (self.__size ** 2)