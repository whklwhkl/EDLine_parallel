# EDLine-api

## Prerequisites
`pip install flask`

## Launch
```bash
PYTHONPATH=. python ./api/app.py
```

## Methods

### line detection
- input: file named `image`
- output: list of [x1, y1, x2, y2] indicating each line segment

#### example
```bash
curl -F image=@data/test.png http://localhost:5000
```

### parameter configurations
- input: param names and values
- output: altered params


#### examples
```bash
curl 'localhost:5000/set?kernel=5&sigma=2'  # multiple alternation
curl 'localhost:5000/set?kernel=5'
curl 'localhost:5000/set'  # do nothing
```
#### parameters
- kernel
- sigma
- gradient_threshold
- anchor_threshold
- scan_interva
- min_line_len
- line_fit_err_threshold
