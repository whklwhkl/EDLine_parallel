import cv2
import edline
import numpy as np


def main():
    param = [5, 1.0, 30, 5, 2, 25, 1.8]
    line_detctor = edline.EDLine(*param)
    lines = edline.LineList()
    img = cv2.imread("./data/test.png", 0)  # readin gray
    assert img is not None
    line_detctor.detect(img, lines, False)
    img = cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)
    for l in lines:
        x1, y1, x2, y2 = map(int, l.endpoint)
        r, g, b = np.random.randint(0, 255, [3]).tolist()
        cv2.line(img, (x1, y1), (x2, y2), (r, g, b))
    cv2.imwrite('demo.png', img)


if __name__ == '__main__':
    main()
