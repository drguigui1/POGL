# version 460 core

out vec4 FragColor;

in vec3 color;
in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

uniform float iTime;


float hash( in vec2 p )
{
    return fract(sin(p.x*15.32+p.y*35.78) * 43758.23);
}

vec2 hash2(vec2 p)
{
	return vec2(hash(p*.754),hash(1.5743*p.yx+4.5891))-.5;
}


vec2 add = vec2(1.0, 0.0);

vec2 noise2(vec2 x)
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);

    vec2 res = mix(mix( hash2(p),          hash2(p + add.xy),f.x),
                    mix( hash2(p + add.yx), hash2(p + add.xx),f.x),f.y);
    return res;
}

vec2 noise2b( in vec2 p )// Simplex Noise from IQ
{
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;
	p /=2.;
	vec2 i = floor( p + (p.x+p.y)*K1 );

    vec2 a = p - i + (i.x+i.y)*K2;
    vec2 o = (a.x>a.y) ? vec2(1.0,0.0) : vec2(0.0,1.0); //vec2 of = 0.5 + 0.5*vec2(sign(a.x-a.y), sign(a.y-a.x));
    vec2 b = a - o + K2;
	vec2 c = a - 1.0 + 2.0*K2;

    vec3 h = max( 0.5-vec3(dot(a,a), dot(b,b), dot(c,c) ), 0.0 );

	vec3 nx = h*h*h*h*vec3( dot(a,hash2(i+0.0)), dot(b,hash2(i+o)), dot(c,hash2(i+1.0)));
    vec3 ny = h*h*h*h*vec3( dot(a,hash2(i+4.5)), dot(b,hash2(i+o+4.5)), dot(c,hash2(i+1.0+4.5)));

    return vec2(dot( nx, vec3(70.0) ),dot( ny, vec3(70.0) ));

}

vec2 fbm2(vec2 x)
{
    vec2 r = vec2(0.0);
    float a = 1.0;

    for (int i = 0; i < 8; i++)
    {
        r += abs(noise2(x)+.5 )* a;
        x *= 2.;
        a *= .5;
    }

    return r;
}

mat2 m2;

vec2 fbm3(vec2 x)
{
    vec2 r = vec2(0.0);
    float a = 1.;

    for (int i = 0; i < 6; i++)
    {
        r += m2*noise2b((x+r)/a)*a;
        r=-.8*abs(r);
        a*=1.7;
    }
    return r;
}

vec3 storm(vec2 x)
{
    float t = .2*iTime;
    float st = sin(t), ct = cos(t);
    m2 = mat2(ct,st,-st,ct);
    x=fbm3(x+t)+2.;
    x*=.35;


    float c = length(x);
    c=c*c*c;//pow(c,3.);
    vec3 col=vec3(0.6-.1*x.x,0.7,0.8-.1*x.y)*c*x.y;
    return clamp(col,0.,1.);
}

float dseg( vec2 ba, vec2 pa )
{

	float h = clamp( dot(pa,ba)/dot(ba,ba), -0.2, 1. );
	return length( pa - ba*h );
}

float arc(vec2 x,vec2 p, vec2 dir)
{
    vec2 r = p;
    float d=10.;
    for (int i = 0; i < 5; i++)
    {
        vec2 s= noise2(r+iTime)+dir;
        d=min(d,dseg(s,x-r));
        r +=s;
    }
    return d*3.;

}

float thunderbolt(vec2 x,vec2 tgt)
{
    vec2 r = tgt+5.*sin(tgt+.3*iTime);
    float d=1000.;
    float dist=length(tgt-x);

    for (int i = 0; i < 19; i++)
    {
        if(r.y>x.y+.5)break;
        vec2 s= (noise2(r)+vec2(0.,.7))*4.;
        dist = dseg(s,x-r);
        d=min(d,dist);

        r +=s;
        if(i-(i/5)*5==0){
            if(i-(i/10)*10==0)d=min(d,arc(x,r,vec2(.3,.5)));
            else d=min(d,arc(x,r,vec2(-.3,.5)));
        }
    }
    return exp(-5.*d)+.2*exp(-1.*dist);

}


void main()
{
	vec2 uv = 2.* texCoord.xy;
    uv*=20.;
    uv.y=40.-uv.y;

    vec3 col=storm(uv);
    float c = thunderbolt(uv+1.*fbm2(uv),vec2(10.));
    c+=thunderbolt(uv+1.*fbm2(uv),vec2(20.));
    c+=thunderbolt(uv+1.*fbm2(uv),vec2(50.,10.));
    col+=clamp(1.7*vec3(0.8,.7,.9)*c,0.,1.);

	FragColor = vec4(col,1.0);
}
