import React, { useState, useEffect, useCallback, useRef } from 'react';

/** 무한 스크롤 감도 */
export const INTERSECTION_OBSERVER_THRESHOLD: number = 1.0; // 0.1 ~ 0.5도 좋음

/** InfiniteScrollProps */
type InfiniteScrollProps<T> = {
    items: T[];
    batchSize: number; // 한 번에 불러올 데이터 묶음 크기
    options?: {
        resetOnItemsChange?: boolean; // items가 바뀌었을 때 사이즈 초기화 여부 (기본값: false)
        intersectionObserverThreshold?: number; // 무한 스크롤 감도 (기본값: 1.0)
    };

    children: (visibleItems: T[]) => React.ReactNode;
};

/** 무한 스크롤 레이아웃 */
const InfiniteScrollLayout = <T,>(props: InfiniteScrollProps<T>) => {
    const { children, items, batchSize, options = {} } = props;
    const { resetOnItemsChange = false, intersectionObserverThreshold = INTERSECTION_OBSERVER_THRESHOLD } = options;

    // 현재 화면에 보여줄 항목 수
    const [displayCount, setDisplayCount] = useState<number>(batchSize);
    useEffect(() => {
        if (resetOnItemsChange) {
            setDisplayCount(batchSize);
        }
    }, [items]);

    // IntersectionObserver 참조용
    const observerTarget = useRef<HTMLDivElement>(null);

    // 무한 스크롤 콜백
    const onIntersect: IntersectionObserverCallback = useCallback(
        entries => {
            if (entries[0].isIntersecting && displayCount < items.length) {
                setDisplayCount(prev => Math.min(prev + batchSize, items.length));
            }
        },
        [displayCount, items.length],
    );

    useEffect(() => {
        const observer = new IntersectionObserver(onIntersect, {
            root: null,
            rootMargin: '0px',
            threshold: intersectionObserverThreshold,
        });
        if (observerTarget.current) observer.observe(observerTarget.current);

        return () => {
            if (observerTarget.current) observer.unobserve(observerTarget.current);
        };
    }, [onIntersect]);

    const visibleItems: T[] = items.slice(0, displayCount);

    return (
        <>
            {children(visibleItems)}

            {/* IntersectionObserver용 빈 div */}
            <div ref={observerTarget} className="h-[1px] w-full" />
        </>
    );
};

export default InfiniteScrollLayout;
