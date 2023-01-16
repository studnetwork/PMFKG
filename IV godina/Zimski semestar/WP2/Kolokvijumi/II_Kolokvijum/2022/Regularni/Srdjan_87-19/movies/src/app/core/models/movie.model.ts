import { Actor } from "./actor.model";
import { Rating } from "./rating.model";

export interface Movie {
    _id: string;
    title: string;
    genres: [string];
    ratings: [Rating];
    actors: [Actor];
}
