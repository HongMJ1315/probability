/*
            Mat img(400, 600, CV_8UC3, Scalar(255, 255, 255));
            int max = 0;
            for(int i = 0; i <= mxn; i++){
                if(hist[i] > max)
                    max = hist[i];
            }
            for(int i = 0; i <= mxn; i++){
                int x = i * 600 / mxn;
                int y = 400 - hist[i] * 400 / max;
                rectangle(img, Point(x, 400), Point(x + 5, y), Scalar(0, 0, 0), -1);
            }
            video << img;
            */