import cv2
import edline
import flask
import numpy as np

from flask import Flask, request, jsonify


app = Flask(__name__)
names = ['kernel', 'sigma', 'gradient_threshold', 'anchor_threshold', 'scan_interval', 'min_line_len', 'line_fit_err_threshold']
types = [int, float, float, float, int, int, float]
param = [5, 1.0, 30, 5, 2, 25, 1.8]
line_detctor = edline.EDLine(*param)


@app.route('/set')
def config():
    global line_detctor, param
    for i, n in enumerate(names):
        param[i] = types[i](request.args.get(n, param[i]))
    line_detctor = edline.EDLine(*param)
    return '\n'.join([f'{k}: {v}' for k, v in zip(names, param)]) + '\n'


@app.route('/', methods=['POST'])
def det():
    img_f = request.files['image']
    img_b = np.array(bytearray(img_f.read()), dtype=np.uint8)
    img = cv2.imdecode(img_b, 0)  # gray
    lines = edline.LineList()
    line_detctor.detect(img, lines, False)
    return jsonify([l.endpoint for l in lines])


def main():
    app.run('0.0.0.0', debug=True)


if __name__ == '__main__':
    main()
