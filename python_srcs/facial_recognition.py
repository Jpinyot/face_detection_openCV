 # Change scaleFactor to get difference results.

import cv2
import sys

 # Initial values HAARCASCADE/IMAGE
faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
initial_image = cv2.imread(sys.argv[1])
gray_image = cv2.cvtColor(initial_image, cv2.COLOR_BGR2GRAY)

 # Detect faces in the image
faces = faceCascade.detectMultiScale(gray_image, scaleFactor=1.2, minNeighbors=5, minSize=(30, 30))

print("We found {0} faces.".format(len(faces)))

 # Mark found faces
for (x, y, w, h) in faces:
    cv2.rectangle(initial_image, (x, y), (x+w, y+h), (0, 255, 0), 2)

cv2.imshow("Faces found", initial_image)
cv2.waitKey(5000)
