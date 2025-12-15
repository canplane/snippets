/**
 * decorator 없이 자동으로 MobX store를 생성 가능하도록 하는 함수
 *
 * observable 자동화에 이용되는 mobx.makeAutoObservable 함수와 유사하나,
 * 해당 함수는 상속 관계에서는 동작하지 않는 이슈가 존재하여 해당 문제를 해결하기 위해 추가
 *
 * From: https://gist.github.com/stephenh/77f62941913203a871d0e284ea779fe9
 *
 * Usage: `
 *      class FooStore {
 *          ...
 *          constructor(...) {
 *              ...
 *
 *              if (new.target === FooStore) {
 *                  makeSimpleAutoObservable(this);
 *              }
 *          }
 *          ...
 *      }
 * `
 */

import { $mobx, isObservable, makeObservable } from 'mobx';

const annotationsSymbol = Symbol('annotationsSymbol');
const objectPrototype = Object.prototype;

/**
 * A purposefully-limited version of `makeAutoObservable` that supports subclasses.
 *
 * There is valid complexity in supporting `makeAutoObservable` across disparate/edge-casey
 * class hierarchies, and so mobx doesn't support it out of the box. See:
 * https://github.com/mobxjs/mobx/discussions/2850#discussioncomment-1203102
 *
 * So this implementation adds a few limitations that lets us get away with it. Specifically:
 *
 * - We always auto-infer a key's action/computed/observable, and don't support user-provided config values
 * - Subclasses should not override parent class methods (although this might? work)
 * - Only the "most child" subclass should call `makeSimpleAutoObservable`, to avoid each constructor in
 *   the inheritance chain potentially re-decorating keys.
 *
 * See https://github.com/mobxjs/mobx/discussions/2850
 */
const makeSimpleAutoObservable = (target: any, overrides: any = {}, options: any = { autoBind: true }): void => {
    // // These could be params but we hard-code them
    // const overrides = {} as any;
    // const options = { autoBind: true };

    // Make sure nobody called makeObservable/etc. previously (eg in parent constructor)
    if (isObservable(target)) {
        throw new Error('Target must not be observable');
    }

    let annotations = target[annotationsSymbol];
    if (!annotations) {
        annotations = {};
        let current = target;
        while (current && current !== objectPrototype) {
            Reflect.ownKeys(current).forEach(key => {
                if (key === $mobx || key === 'constructor') return;
                // eslint-disable-next-line no-nested-ternary
                annotations[key] = !overrides ? true : key in overrides ? overrides[key] : true;
            });
            current = Object.getPrototypeOf(current);
        }
        // Cache if class
        const proto = Object.getPrototypeOf(target);
        if (proto && proto !== objectPrototype) {
            Object.defineProperty(proto, annotationsSymbol, { value: annotations });
        }
    }

    return makeObservable(target, annotations, options);
};

export default makeSimpleAutoObservable;
