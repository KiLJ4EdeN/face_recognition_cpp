# face_recognition_cpp
Facial Recognition with cpp using state of the art insightface model.

### DONE
functionallity to compare two images using cosine distance.

### TODO
saveable embeddings to collect a database of faces and do 1 to N comparisons.


# usage
Download the model .pb file from [URL](https://drive.google.com/open?id=1Iw2Ckz_BnHZUi78USlaFreZXylJj7hnP)

The Main Python Project is at [URL](https://github.com/AIInAi/tf-insightface)

```bash
# install opencv.
cd thirdparty
wget https://github.com/opencv/opencv/archive/2.4.13.5.zip
bash opencv.sh
cd ..
# build the project.
buildproj.sh
```


# run
```bash
cp PATH_TO_MODEL/insightface.cpp PATH_TO_REPO/models
cd PATH_TO_REPO
./bin/match IMAGE1_PATH IMAGE2_PATH 
# ex ./bin/match images/test.jpg images/test.jpg
```
