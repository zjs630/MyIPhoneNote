1,步骤
Create a UIDynamicAnimator
Add UIDynamicBehaviors to it(gravity,collisions,etc.)
Add UIDynamicItems(usually UIViews)to the UIDynamicBehaviors

例如：
UIDynamicAnimator *animator = [[UIDynamicAnimator alloc] initWithReferenceView:self.view];
UIGravityBehavior *behavior = [[UIGravityBehavior alloc] initWithItems:@[self.gzImageView]];
[animator addBehavior:behavior];