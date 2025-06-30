#pragma warning (disable : 4244) // rozne typy
#pragma warning (disable : 4305)

#include "Tween.h"

Tween::Tween()
{
    
}

Tween::Tween(int iSize)
{
    for (int i=0; i<iSize; ++i)
        _pTable.push_back(0);    
}

Tween::Tween(float fv1, float fv2, int i)
{
    _fV1 = fv1; _fV2 = fv2;

    for (int j=0; j<i; j++)
        _pTable.push_back(0);
}

Tween::Tween(float fv1, float fv2, float f)
{
    float step, fstart;

    _fV1 = fv1; _fV2 = fv2;
   
    step = float((fv2-fv1)/f);

    fstart = fv1;
    
    while (fstart!=fv2)
    {
        _pTable.push_back(0);
        fstart += step;
    }
    
}

Tween::Tween(float fv1, float fv2)
{
    _fV1 = fv1; _fV2 = fv2;
}

Tween::~Tween()
{
    _pTable.clear();
}

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float Tween::back(float t)
{
    float fValue;
    float s = 1.70158f;
    fValue =  t * t * ( (s+1) * t - s);
    return _fV1+((_fV2 - _fV1)*fValue);
}

float Tween::back(float f1, float f2, float t)
{
    float fValue;
    float s = 1.70158f;
    
    _fV1 = f1; _fV2 = f2;
    
    fValue =  t * t * ( (s+1) * t - s);
    return _fV1+((_fV2 - _fV1)*fValue);
}


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float Tween::bounce( float t )
{
    const float v = 1 - t;
    float fValue,c,d;
    
    if ( v < (1 / 2.75) )
    {
        c = v;
        d = 0;
    }
    else if ( v < (2 / 2.75) )
    {
        c = v - 1.5 / 2.75;
        d = 0.75;
    }
    else if ( v < (2.5 / 2.75) )
    {
        c = v - 2.25 / 2.75;
        d = 0.9375;
    }
    else
    {
        c = v - 2.625 / 2.75;
        d = 0.984375;
    }
    
    fValue = 1 - (7.5625 * c * c + d);

    return _fV1+((_fV2 - _fV1)*fValue);
}

float Tween::bounce( float f1, float f2, float t )
{
    const float v = 1 - t;
    float fValue,c,d;

    _fV1 = f1; _fV2 = f2;    
    
    if ( v < (1 / 2.75) )
    {
        c = v;
        d = 0;
    }
    else if ( v < (2 / 2.75) )
    {
        c = v - 1.5 / 2.75;
        d = 0.75;
    }
    else if ( v < (2.5 / 2.75) )
    {
        c = v - 2.25 / 2.75;
        d = 0.9375;
    }
    else
    {
        c = v - 2.625 / 2.75;
        d = 0.984375;
    }
    
    fValue = 1 - (7.5625 * c * c + d);
    
    return _fV1+((_fV2 - _fV1)*fValue);
}

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float Tween::circ( float t )
{
    float fValue = 1 - sqrt(1 - t * t);
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_circ_func()

float Tween::circ( float f1, float f2, float t )
{
    float fValue = 1 - sqrt(1 - t * t);
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*fValue);    
} // easing_circ_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float Tween::cubic( float t )
{
    float fValue = t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_cubic_func()

float Tween::cubic( float f1, float f2, float t )
{
    float fValue = t * t * t;
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_cubic_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float Tween::elastic( float t )
{
    const float pi(3.1415927);
    float v(t-1);
    const float p(0.3);
    
    float fValue = -pow(2, 10 * v) * sin( (v - p / 4) * 2 * pi / p );
    return _fV1+((_fV2 - _fV1)*fValue);

} // easing_elastic_func()

float Tween::elastic( float f1, float f2, float t )
{
    const float pi(3.1415927);
    float v(t-1);
    const float p(0.3);

    _fV1 = f1; _fV2 = f2;
    
    float fValue = -pow(2, 10 * v) * sin( (v - p / 4) * 2 * pi / p );
    return _fV1+((_fV2 - _fV1)*fValue);
    
} // easing_elastic_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */

float Tween::expo( float t )
{
    float fValue = t == 0 ? 0 : pow(2, 10 * (t - 1));
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_expo_func()

float Tween::expo( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue = t == 0 ? 0 : pow(2, 10 * (t - 1));
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_expo_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float Tween::linear( float t )
{
    return _fV1+((_fV2 - _fV1)*t);
} // easing_linear_func()

float Tween::linear( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*t);
} // easing_linear_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float Tween::quad( float t )
{
    float fValue =  t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quad_func()

float Tween::quad( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue =  t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quad_func()

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float Tween::quart( float t )
{
    float fValue = t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quart_func()

float Tween::quart( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue = t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quart_func()


/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float Tween::quint( float t )
{
    float fValue = t * t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quint_func()

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float Tween::quint( float f1, float f2, float t )
{
    _fV1 = f1; _fV2 = f2;
    float fValue = t * t * t * t * t;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_quint_func()

/**
 * \brief The default function.
 * \param t The ratio of the date, in (0, 1), representing the total
 *        progression of the tweener.
 */
float Tween::sine( float t )
{
    const float pi(3.1415927);
    float fValue = 1 - cos(t * pi / 2);
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_sine_func()

float Tween::sine( float f1, float f2, float t )
{
    const float pi( 3.1415927 );
    float fValue = 1 - cos(t * pi / 2);
    _fV1 = f1; _fV2 = f2;
    return _fV1+((_fV2 - _fV1)*fValue);
} // easing_sine_func()




