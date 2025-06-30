//
//  UIView_ProfileIO_h.h
//  Gems Of Atlantis
//
//  Created by Jarek on 13.03.2014.
//
//

#import <UIKit/UIKit.h>

- (unsigned long)getScore :
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    unsigned long ulScore = [defaults integerForKey:@"GOA_ulScore"];
   
    return ulScore;
}

- (void)setScore:(unsigned long)ulScore
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];

    [defaults setInteger:ulScore forKey:@"GOA_ulScore"];
    
}