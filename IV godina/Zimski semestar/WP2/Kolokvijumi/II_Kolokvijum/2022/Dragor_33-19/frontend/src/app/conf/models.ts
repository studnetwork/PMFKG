export interface Jwt {
    _id: string
    expire: number
    iat: number
}

export interface LoginModel {
    email: string
    password: string
}

export interface RegisterModel {
    name: string
    email: string
    password: string
}

export interface ActorModel {
    _id: string
    name: string
    movies: string[]
}

export interface RatingModel {
    _id: string
    user: string
    rating: number
}

export interface MovieModel {
    _id: string
    title: string
    genres: string[]
    actors: ActorModel[]
    ratings: RatingModel[]
}