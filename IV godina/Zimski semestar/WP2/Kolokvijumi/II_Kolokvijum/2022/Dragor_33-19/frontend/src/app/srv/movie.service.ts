import { HttpClient, HttpResponse } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { api } from '../conf/api';
import { MovieModel } from '../conf/models';

@Injectable({
  providedIn: 'root'
})
export class MovieService {

  constructor(
    private http: HttpClient
  ) { }

  getAllMovies(): Observable<HttpResponse<MovieModel[]>> {
    return this.http.get<MovieModel[]>(
      `${api.host}/movies`, { observe: 'response' }
    )
  }
  
  getRatedMovies(): Observable<HttpResponse<MovieModel[]>> {
    return this.http.get<MovieModel[]>(
      `${api.host}/rated`, { observe: 'response' }
    )
  }
    
  rateMovie(id: string, rating: number): Observable<HttpResponse<boolean>> {
    return this.http.post<boolean>(
      `${api.host}/movies/rate/${id}`, { rating: rating }, { observe: 'response' }
    )
  }

}
