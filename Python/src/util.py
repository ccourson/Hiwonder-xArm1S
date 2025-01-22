class Util:
    @staticmethod
    def _lerp(i, j, k):
        return float((1 - k) * i + j * k)

    @staticmethod
    def _invlerp(i, j, k):
        return float((k - i) / (j - i))

    @staticmethod
    def _x_round(x):
        return float(round(x*4) / 4)

    @staticmethod
    def _angle_to_position(degrees):
        if not isinstance(degrees, float) or degrees < -125.0 or degrees > 125.0:
            raise ValueError('Parameter \'degrees\' must be a float value between -125.0 and 125.0')
        x = Util._x_round(degrees)
        y = Util._invlerp(-125.0, 125.0, x)
        return int(Util._lerp(0, 1000, y))

    @staticmethod
    def _position_to_angle(position):
        if not isinstance(position, int) or position < 0 or position > 1000:
            raise ValueError('Parameter \'position\' must be and int value between 0 and 1000')

        return Util._lerp(-125.0, 125.0, position / 1000)