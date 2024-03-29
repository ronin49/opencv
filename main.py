import numpy as np
# This scripts uses OpenCV to capture webcam output, applies a filter,
# and sends it to the virtual camera.
# It also shows how to use BGR as pixel format.

import argparse
import cv2
import pyvirtualcam
from pyvirtualcam import PixelFormat

parser = argparse.ArgumentParser()
parser.add_argument("--camera", type=int, default=0, help="ID of webcam device (default: 0)")
parser.add_argument("--fps", action="store_true", help="output fps every second")
parser.add_argument("--filter", choices=["shake", "none"], default="shake")
args = parser.parse_args()

# Set up webcam capture.
vc = cv2.VideoCapture(args.camera)
cap = cv2.VideoCapture('porn.mp4')
if not vc.isOpened():
    raise RuntimeError('Could not open video source')

pref_width = 1280
pref_height = 720
pref_fps_in = 30
vc.set(cv2.CAP_PROP_FRAME_WIDTH, pref_width)
vc.set(cv2.CAP_PROP_FRAME_HEIGHT, pref_height)
vc.set(cv2.CAP_PROP_FPS, pref_fps_in)

# Query final capture device values (may be different from preferred settings).
width = int(vc.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(vc.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps_in = vc.get(cv2.CAP_PROP_FPS)
print(f'Webcam capture started ({width}x{height} @ {fps_in}fps)')

fps_out = 20

with pyvirtualcam.Camera(width, height, fps_out, fmt=PixelFormat.BGR, print_fps=args.fps) as cam:
    print(f'Virtual cam started: {cam.device} ({cam.width}x{cam.height} @ {cam.fps}fps)')

    # Shake two channels horizontally each frame.
    channels = [[0, 1], [0, 2], [1, 2]]

    while True:
        # Read frame from webcam.
        ret, frame = vc.read()
        if not ret:
            raise RuntimeError('Error fetching frame')

        if args.filter == "shake":
            pass
            dx = 15 - cam.frames_sent % 5
            c1, c2 = channels[cam.frames_sent % 3]
            frame[:,:-dx,c1] = frame[:,dx:,c1]
            frame[:,dx:,c2] = frame[:,:-dx,c2]

        ret, fire = cap.read()
        fire = cv2.resize(fire,(1280,720))
        cam.send(cv2.addWeighted(fire, 0.6, frame, 0.4, 0.0))
                
        frame = cv2.GaussianBlur(frame, (3, 3), 0)


        scale = 1
        delta = 0
        ddepth = cv2.CV_16S
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)


        grad_x = cv2.Sobel(gray, ddepth, 1, 0, ksize=3, scale=scale, delta=delta, borderType=cv2.BORDER_DEFAULT)
        # Gradient-Y
        # grad_y = cv.Scharr(gray,ddepth,0,1)
        grad_y = cv2.Sobel(gray, ddepth, 0, 1, ksize=3, scale=scale, delta=delta, borderType=cv2.BORDER_DEFAULT)


        abs_grad_x = cv2.convertScaleAbs(grad_x)
        abs_grad_y = cv2.convertScaleAbs(grad_y)


        frame = cv2.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)
        frame = cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)

        # Send to virtual cam.
        #cam.send(frame)

        # Wait until it's time for the next frame.
        cam.sleep_until_next_frame()

