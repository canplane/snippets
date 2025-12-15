import React, { useState, useEffect } from 'react';

/** ShowMoreProps */
type ShowMoreProps<T> = {
    items: T[];
    batchSize: number; // 한 번에 불러올 데이터 묶음 크기
    options?: {
        resetOnItemsChange?: boolean; // items가 바뀌었을 때 사이즈 초기화 여부 (기본값: false)
    };

    children: (visibleItems: T[]) => React.ReactNode;
    trigger: (onClick: () => void) => React.ReactNode;
};

/** 더 보기 레이아웃 */
const ShowMoreLayout = <T,>(props: ShowMoreProps<T>) => {
    const { children, trigger, items, batchSize, options = {} } = props;
    const { resetOnItemsChange = false } = options;

    // 현재 화면에 보여줄 항목 수
    const [displayCount, setDisplayCount] = useState<number>(batchSize);
    useEffect(() => {
        if (resetOnItemsChange) {
            setDisplayCount(batchSize);
        }
    }, [items]);

    // 더 보기 버튼 클릭 시
    const handleShowMore = (): void => {
        setDisplayCount(prev => Math.min(prev + batchSize, items.length));
    };

    const visibleItems: T[] = items.slice(0, displayCount);

    return (
        <>
            {children(visibleItems)}

            {displayCount < items.length && trigger(handleShowMore)}
        </>
    );
};

export default ShowMoreLayout;
