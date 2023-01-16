import { Component, OnInit } from '@angular/core';
import { MovieModel } from 'src/app/conf/models';
import { JwtService } from 'src/app/srv/jwt.service';
import { MovieService } from 'src/app/srv/movie.service';

@Component({
  selector: 'app-home',
  template: `
    <h1>Home</h1>
    
    <b>Movies:</b>
    <ul *ngIf="movies">
      <li *ngFor="let m of movies; index as i">
        <button (click)="selectMovie(i)">{{m.title}}</button>
      </li>
    </ul>
    <br>
    
    <div *ngIf="selectedMovie">
      <b>{{selectedMovie.title}}</b>
      <div>Actors:</div>
      <ul>
        <li *ngFor="let a of selectedMovie.actors">{{a.name}}</li>
      </ul>
    </div>
    <br>

    <div *ngIf="canRate()">
      <input type="number" [(ngModel)]="rating">
      <button (click)="rateMovie()">Rate</button>
    </div>
  `
})
export class HomeComponent implements OnInit {

  movies: MovieModel[] | null = null
  selectedMovie: MovieModel | null = null
  
  rating: number = 0

  constructor(
    private movieService: MovieService,
    private jwtService: JwtService
  ) { }

  ngOnInit() {
    this.getAllMovies()
  }

  selectMovie(index: number) {
    if(this.movies)
      this.selectedMovie = this.movies[index]
  }

  rateMovie() {
    if(this.selectedMovie) {
      this.movieService.rateMovie(this.selectedMovie._id, this.rating)
      .subscribe({
        next: (res) => { console.log(res.body) },
        error: (err) => {}
      })
    }
  }

  canRate() {
    return !this.jwtService.isJwtExpired() && this.selectedMovie
  }

  getAllMovies() {
    this.movieService.getAllMovies()
    .subscribe({
      next: (res) => { 
        if(res.body)
          this.onGetAllMoviesSuccess(res.body) 
      },
      error: (err) => {
        console.log('Get All Movies Error')
      }
    })
  }

  onGetAllMoviesSuccess(movies: MovieModel[]) {
    this.movies = movies
  }

}
