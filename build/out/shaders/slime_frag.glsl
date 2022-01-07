#version 110

varying vec4 pos;   

uniform mat4 MVP;
uniform float time;
uniform float breath_speed;
uniform vec2 collision;//.x -> collision left , .y -> collision right 
                        //(value is collision impact use (0.0 ; 2.0) values)

float line_len(float x, float y ,float x1, float y1)
{
   return sqrt((x - x1)*(x - x1) + (y - y1) * (y - y1));
}

void main()
{
    float breath = (1.0 + abs(sin(time  * breath_speed) * 0.1));
    vec2 slime_pos = vec2(pos.x / breath, (pos.y + 1.0) * breath) * 1.1;

    if(slime_pos.x > 0.0)  slime_pos.x += slime_pos.x * collision.x; //collision right
    if(slime_pos.x < 0.0)  slime_pos.x += slime_pos.x * collision.y; //collision left

    float alpha = (20.0 - 20.0 * line_len(0.0, 0.0, slime_pos.x, slime_pos.y)) 
      * abs(slime_pos.y);

    gl_FragColor = vec4(0.1, 0.4, 0.6 * abs(sin(time * 0.4 + slime_pos.x)), alpha * 0.6);
    gl_FragColor.rgb *= 1.8;//make more brigter
}