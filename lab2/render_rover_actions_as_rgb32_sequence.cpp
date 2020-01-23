#include "rover.hpp"

#include "rover_action.hpp"

#include <vector>
#include <algorithm>
#include <cmath>



/* Represents an image over the range [-1,+1] x [-1,+1] */
class Image
{
private:
    int width, height;
    vector<float> pixels; // Array of RGB pixels between 0 and 1
public:
    Image(int _width, int _height)
    {
        width=_width;
        height=_height;
        pixels.assign(3*width*height, 0);
    }

    /* Draws a line by a simple over-sampling method */
    void draw_line(vector2d p0, vector2d p1, float r, float g, float b)
    {
        assert( 0<=r && r<=1 );
        assert( 0<=g && g<=1 );
        assert( 0<=b && b<=1 );

        cerr << p0.x << "," << p0.y << "->" << p1.x << "," << p1.y << endl;

        // Map the co-ordinates in [-1,+1)x[-1,+1) -> [0,width)x[0,height)
        int p0x=int( (p0.x+1)/2 * width );
        int p0y=int( (p0.y+1)/2 * height );
        int p1x=int( (p1.x+1)/2 * width );
        int p1y=int( (p1.y+1)/2 * height );

        int points=1024; //max(width,height);
        float p_step=1.0/points;

        for(float alpha=0.0; alpha<1.0; alpha+=p_step){
            int x = alpha * p0x + (1-alpha) * p1x;
            int y = alpha * p0y + (1-alpha) * p1y;

            if(0 <= x && x < width && 0 <= y && y < height ){
                pixels[ 3 * width * y + 3*x + 0 ] = r;
                pixels[ 3 * width * y + 3*x + 1 ] = g;
                pixels[ 3 * width * y + 3*x + 2 ] = b;
            }
        }
    }

    void render_as_rgb32(ostream &dst)
    {
        vector<uint8_t> out;
        out.resize(width*height*4);
        int index=0;
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                out[index++] = (int)(255*pixels[3*width*y+3*x+0]);
                out[index++] = (int)(255*pixels[3*width*y+3*x+1]);
                out[index++] = (int)(255*pixels[3*width*y+3*x+2]);
                index++;
            }
        }
        cout.write((char *)&out[0], out.size());
        cout.flush();
    }

    void blend(const Image &o, float fade)
    {
        assert(width==o.width);
        assert(height==o.height);

        for(int i=0; i<pixels.size(); i++){
            pixels[i] = min(1.0f, pixels[i] + o.pixels[i] * fade);
        }
    }
};

int main(int argc, const char **argv)
{
    int width=512;
    int height=512;
    // We want to render at 25 fps
    float frames_per_second = 25;
    float frame_time_step = 1.0/frames_per_second;

    float fade=0.995;

    if(argc > 1){
        fade=stof(argv[1]);
    }

    // The rover we are going to replay the actions on.
    Rover rover;

    // This is an image holding the accumulated trail from previous steps
    Image history(width,height);

    float next_frame_time=frame_time_step;

    RoverAction action;
    while(1){
        assert( rover.get_time() < next_frame_time );

        cin >> action;
        if(cin.fail()){
            break;
        }

        cerr << action << endl;

        // Transfer the incoming state into the rover
        rover.set_angle(action.angle);
        rover.set_speed(action.speed);
        rover.set_pen_down(action.pen_down);

        cerr << "pen_down = "<<action.pen_down<<endl;

        // We have an action to work with, but it might be longer
        // than the current frame time so we need to chunk it up.
        while(action.dt > 0){
            assert( rover.get_time() < next_frame_time );

            float time_step = max(1e-4f, min( next_frame_time - rover.get_time() , action.dt ));

            cerr << " time step = " << time_step << ", rover.get_time() = " << rover.get_time() <<", next_frame_time = "<<next_frame_time<< endl;

            vector2d starting_pos=rover.get_position();

            // advance the rover by a fraction of time
            rover.advance_time( time_step );
            action.dt-=time_step;

            if( rover.get_time() >= next_frame_time ){
                Image current(width,height);

                if(action.pen_down){
                    current.draw_line(starting_pos, rover.get_position(), 0, 1, 0);
                }

                current.blend(history, fade);
                history=current;

                current.render_as_rgb32(cout);

                next_frame_time += frame_time_step;

                cerr << "t="<<rover.get_time()<<"\n";
            }
        }

    }
}


////////////////////////////////////////////////////////////////

/* Embedded rover logic. Bit of a hack */

Rover::Rover()
{
    m_time=0;
    m_angle=0;
    m_position={0,0};
    m_speed=0;
    m_pen_down=false;
}

Rover::~Rover()
{
}

float Rover::get_time() const
{
    return m_time;
}

vector2d Rover::get_position() const
{
    return m_position;
}

float Rover::get_speed() const
{
    return m_speed;
}

float Rover::get_angle() const
{
    return m_angle;
}

bool Rover::get_pen_down() const
{
    return m_pen_down;
}

void Rover::set_speed(float speed)
{
    assert(speed >= 0);
    m_speed=speed;
}

void Rover::set_angle(float angle)
{
    m_angle=angle;
}

void Rover::set_pen_down(bool pen_down)
{
    m_pen_down=pen_down;
}

void Rover::advance_time(float dt)
{
    vector2d p = m_position;
    vector2d direction = vector2d{ cos(m_angle) , sin(m_angle) } ;
    vector2d pn = m_position + direction * dt * m_speed;

    m_time += dt;
    m_position=pn;
}
