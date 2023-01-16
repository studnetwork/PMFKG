import { Component } from '@angular/core';
import { MovieModel } from 'src/app/conf/models';
import { MovieService } from 'src/app/srv/movie.service';

@Component({
  selector: 'app-profile',
  template: `
    <h1>Profile</h1>
    
    <b>Movies:</b>
    <ul *ngIf="movies">
      <li *ngFor="let m of movies; index as i">
        <b>{{m.title}}</b> ({{calcAvgRating(m)}} / 10)
      </li>
    </ul>
    <br>
  `
})
export class ProfileComponent {

  movies: MovieModel[] | null = null

  constructor(
    private movieService: MovieService,
  ) { }

  ngOnInit() {
    this.getRatedMovies()
  }

  calcAvgRating(movie: MovieModel): number {
    let sum = 0
    for(let r of movie.ratings)
      sum += r.rating
    
    let r = sum / movie.ratings.length
    return Math.round(r*100)/100
  }

  getRatedMovies() {
    this.movieService.getRatedMovies()
    .subscribe({
      next: (res) => { 
        if(res.body)
          this.onGetRatedMoviesSuccess(res.body) 
      },
      error: (err) => {
        console.log('Get All Movies Error')
      }
    })
  }

  onGetRatedMoviesSuccess(movies: MovieModel[]) {
    this.movies = movies
  }

}
