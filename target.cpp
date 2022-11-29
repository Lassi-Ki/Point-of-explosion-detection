#include "target.h"

Target::Target(int tem, int pos, QObject *parent) : QObject(parent)
{
    count = 0;
    temperature_threshold = tem;
    position_threshold = pos;
    location.x = 0;
    location.y = 0;
    location.width = 0;
    location.height = 0;

    es = getStructuringElement(MORPH_ELLIPSE, Size{7, 4});
    m_es = getStructuringElement(MORPH_RECT, Size{9, 9});
    gs = {9, 9};
    is_added = false;
}

Target::~Target()
{

}


Mat Target::dealBack(Mat picture)
{
    erode(picture, picture, m_es);
    cvtColor(picture, picture, COLOR_BGR2GRAY);
    GaussianBlur(picture, picture, gs, 0);

    threshold(picture, picture, temperature_threshold, 255, THRESH_BINARY);
    dilate(picture, picture, es, Point(-1, -1), 3);
    //imshow("opencv", picture);
    return picture;
}

void Target::dealBackground(Mat picture)
{
    dilate(picture, background, m_es);
    cvtColor(background, background, COLOR_BGR2GRAY);
    blur(background, background, Size{9, 9});
}

void Target::drawTrack(vector<vector<Point>> cnts, Mat picture)
{
    int b, g, r;
    default_random_engine e;
    uniform_int_distribution<int> u(0, 255);
    e.seed(time(0));
    b = u(e);
    g = u(e);
    r = u(e);
    drawContours(picture, cnts, -1, Scalar(b, g, r));
    imshow("opencv", picture);
}

void Target::drawCircle(Rect ret, Mat picture)
{
    int b, g, r;
    default_random_engine e;
    uniform_int_distribution<int> u(0, 255);
    e.seed(time(0));
    b = u(e);
    g = u(e);
    r = u(e);
    Point c;
    c.x = ret.x;
    c.y = ret.y;
    circle(picture, c, 10, Scalar(b, g, r), -1);
}

void Target::savePicture(String path, Mat picture)
{
    circle(picture, Point((location.x + location.width / 2), (location.y + location.height / 2)), 10, Scalar(0, 0, 255), -1);
    imwrite(path, picture);
}

void Target::track(Mat deal, Mat picture)
{
    vector<vector<Point>> cnts;
    findContours(deal, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    if (arrs.getSize() != 0)
    {
        for (int i = 0; i < arrs.getSize(); i++)
        {
            arrs[i].updateTime();
            if (arrs[i].alive == false)
            {
                location = arrs[i].rect;
                count += 1;
                emit changeCount();
                arrs.remove(i);
                i--;
            }
        }
    }
    if (!cnts.empty())
    {
        int size = cnts.size();
        for (int i = 0; i < size; i++)
        {
            // drawTrack(cnts, picture);
            Arr new_arr = boundingRect(cnts[i]);
            if (arrs.getSize() == 0)
            {
                arrs.append(new_arr);
                continue;
            }
            is_added = false;
            for (int j = 0; j < arrs.getSize(); j++)
            {
                arrs[j].updateTime();
                if (arrs[j].alive == true)
                {
                    if (abs(arrs[j].rect.x - new_arr.rect.x) < position_threshold)
                    {
                        arrs[j].update(new_arr.rect);
                        is_added = true;
                        break;
                    }
                    continue;
                }
                else
                {
                    location = arrs[i].rect;
                    count += 1;
                    emit changeCount();
                    arrs.remove(j);
                    j--;
                    if (arrs.getSize() == 0)
                    {
                        break;
                    }
                }
            }
            if (is_added == false)
            {
                arrs.append(new_arr);
            }
        }
    }

    if (location.x != 0 && location.y != 0)
    {
        circle(picture, Point((location.x + location.width / 2), (location.y + location.height / 2)), 10, Scalar(255, 0, 0), -1);
    }
}

Rect Target::work(Mat picture)
{
    Mat pic_clone = picture.clone();
    save_picture = picture;
    if (background.empty())
    {
        dealBackground(pic_clone);
        return location;
    }
    // 设置可选择的阈值150
    deal = dealBack(pic_clone);
    track(deal, picture);

    return location;
}

void Target::changeTT(int y)
{
    temperature_threshold = y;
}

void Target::changeTO(int y)
{
    position_threshold = y;
}
