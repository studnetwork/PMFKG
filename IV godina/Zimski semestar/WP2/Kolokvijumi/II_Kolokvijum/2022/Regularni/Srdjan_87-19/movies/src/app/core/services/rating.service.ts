import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { environment } from 'src/environments/environment';
import { Movie } from '../models/movie.model';

@Injectable({
  providedIn: 'root'
})
export class RatingService {

  changeRatingUrl = `${environment.backendUrl}/movies/rate`;
  ratedMoviesUrl = `${environment.backendUrl}/rated`;

  constructor(
    private http: HttpClient
  ) { }
  
  rateMovie(movieId: string, rating: number): Observable<boolean> {
    return this.http.post<boolean>(`${this.changeRatingUrl}/${movieId}`, { rating: rating });
  }
  
  ratedMovies(): Observable<Array<Movie>> {
    return this.http.get<Array<Movie>>(this.ratedMoviesUrl);
  }

}
