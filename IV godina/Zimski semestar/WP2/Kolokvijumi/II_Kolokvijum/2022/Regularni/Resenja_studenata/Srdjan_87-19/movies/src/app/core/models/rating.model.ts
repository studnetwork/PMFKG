import { User } from "./user.model";

export interface Rating {
    _id: string;
    user: User;
    rating: number
}
