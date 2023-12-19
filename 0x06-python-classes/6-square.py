#!/usr/bin/python3
"""Define my square """


class Square:
    """My Private instance attribute """

    def __init__(self, size=0, position=(0, 0)):
        """
        Instantiation
        with optional
        """

        self.__size = size
        self.position = position

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

    @property
    def position(self):
        return self.__position

    @position.setter
    def position(self, value):
        if (not isinstance(value, tuple) or
            len(value) != 2 or
            not all(isinstance(i, int)
            and i >= 0 for i in value)
        ):
            raise TypeError("position must be a tuple of 2 positive integers")
        self.__position = value

    def area(self):
        """Public instance method """

        return (self.__size ** self.__size)
    
    def my_print(self):
        """print the square in # """

        if self.__size == 0:
            print()
        else:
            for _ in range(self.__position[1]):
                print()
            for _ in range(self.__size):
                print(" " * self.__position[0] + "#" * self.__size)