import { Movie } from "./movie.model";

export interface Actor {
    _id: string;
    name: string;
    movies: [Movie];
}
