//
//  Copyright 2011 Andrey Tarantsov. Distributed under the MIT license.
//

#import <Foundation/Foundation.h>

@protocol ATPagingViewDelegate;

// a wrapper around UIScrollView in (horizontal) paging mode, with an API similar to UITableView
@interface ATPagingView : UIView {
	// subviews
	UIScrollView *_scrollView;

	// properties
	id<ATPagingViewDelegate> _delegate;
	CGFloat _gapBetweenPages;
	NSInteger _pagesToPreload;

	// state
	NSInteger _pageCount;
	NSInteger _currentPageIndex;
	NSMutableSet *_recycledPages;
	NSMutableSet *_visiblePages;
	BOOL _rotationInProgress;
}

@property(nonatomic, assign) id<ATPagingViewDelegate> delegate;

@property(nonatomic, assign) CGFloat gapBetweenPages;  // default is 20

@property(nonatomic, assign) NSInteger pagesToPreload;  // number of invisible pages to keep loaded to each side of the visible pages, default is 0

@property(nonatomic, readonly) NSInteger pageCount;

@property(nonatomic, assign, readonly) NSInteger currentPageIndex;

- (void)reloadPages;  // must be called at least once to display something

- (UIView *)viewForPageAtIndex:(NSUInteger)index;  // nil if not loaded

- (UIView *)dequeueReusablePage;  // nil if none

- (void)willAnimateRotation;  // call this from willAnimateRotationToInterfaceOrientation:duration:

- (void)didRotate;  // call this from didRotateFromInterfaceOrientation:

@end


@protocol ATPagingViewDelegate <NSObject>

@required

- (NSInteger)numberOfPagesInPagingView:(ATPagingView *)pagingView;

- (UIView *)viewForPageInPagingView:(ATPagingView *)pagingView atIndex:(NSInteger)index;

@optional

- (void)currentPageDidChangeInPagingView:(ATPagingView *)pagingView;

@end


@interface ATPagingViewController : UIViewController <ATPagingViewDelegate> {
}

@property(nonatomic, readonly) ATPagingView *pagingView;

@end
